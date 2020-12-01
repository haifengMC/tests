#include "global.h"
#include "hTest.h"
#include "hTool.h"

using namespace std;

TEST_INIT()
mutex coutM;
#define COUT_LOCK(x) { lock_guard<mutex> lk(coutM); cout << x << endl; }


void pSize1(const char* name, vector<int>& v, size_t n)
{
	while (n--)
	{
		v.push_back(1);
		cout << name << v.size() << "/" << v.capacity() << " ";
	}

	cout << endl;
}

TEST(vector内存分配变化1)
{
	vector<int> v1;
	pSize1("v1", v1, 10);
	vector<int> v2;
	pSize1("v2", v2, 20);
}

void pSize2(const char* name, vector<int>& v, size_t n)
{
	cout << "[" << name << "]" << endl;
	while (n--)
	{
		size_t n = v.size();
		v.resize((n / 10 + 1) * 10);
		cout << v.size() << "/" << v.capacity() << " ";
	}

	cout << endl;
}

TEST(vector内存分配变化2)
{
	vector<int> v1;
	pSize2("v1", v1, 10);
	vector<int> v2;
	pSize2("v2", v2, 20);
}

TEST(realloc分配内存)
{
	void* p1 = malloc(10);
	cout << "<p1>" << p1 << endl;
	void* p2 = realloc(p1, 100);
	cout << "<p1>" << p1 << "<p2>" << p2 << endl;
	void* p3 = realloc(p2, 10000000000000000);
	cout << "<p1>" << p1 << "<p2>" << p2 << "<p3>" << p3 << endl;
	free(p2);
}

//仅维护内存单元，不管理内存数据中的指针
class hAllocItem
{
	void* _ptr = NULL;
	size_t _size = 0;

public:
	hAllocItem() {}
	~hAllocItem() { deallocate(); }
	hAllocItem(const hAllocItem&) = delete;
	hAllocItem(hAllocItem&& item) noexcept;

	bool allocate(size_t size);
	bool reallocate(size_t size);
	bool deallocate();

	operator void* () { return _ptr; }
	operator void* () const { return _ptr; }
	size_t size() const { return _size; }
};	

hAllocItem::hAllocItem(hAllocItem&& item) noexcept
{
	_ptr = item._ptr;
	_size = item._size;

	item._ptr = 0;
	item._size = 0;
}

bool hAllocItem::allocate(size_t size)
{
	deallocate();

	void* ptr = malloc(size);
	if (!ptr)
		return false;

	_ptr = ptr;
	_size = size;
	memset(_ptr, 0, _size);
	return true;
}
bool hAllocItem::reallocate(size_t size)
{
	if (_size == size)
		return true;

	void* ptr = realloc(_ptr, size);
	if (!ptr)
		return false;
	_ptr = ptr;
	if (size > _size)
		memset((uint8_t*)_ptr + _size, 0, size - _size);

	_size = size;

	return true;
}
bool hAllocItem::deallocate()
{
	if (_ptr)
		free(_ptr);

	_ptr = NULL;
	_size = 0;

	return true;
}

//内存分配器
template <typename T, size_t SizeMax = 1024>
class hAlloc
{
	static const size_t sCntMax;
	static const size_t sSizeMax;

	hAllocItem items;
	size_t _num = 0;
public:
	hAlloc() {}
	~hAlloc();


	size_t size() const { return _num; }
	T* operator[] (size_t i);
	const T* operator[] (size_t i) const;

	bool allocate(size_t num);
	bool reallocate(size_t num);
	bool deallocate();
};
template <typename T, size_t SizeMax>
const size_t hAlloc<T, SizeMax>::sCntMax = SizeMax / sizeof(T);
template <typename T, size_t SizeMax>
const size_t hAlloc<T, SizeMax>::sSizeMax = sCntMax * sizeof(T);

#define ITEMS(i) ((hAllocItem*)(void*)items + i)
#define DATAS(i) ((T*)(void*)(*item) + i)
#define CITEMS(i) ((const hAllocItem*)(const void*)items + i)
#define CDATAS(i) ((const T*)(const void*)(*item) + i)

template <typename T, size_t SizeMax>
hAlloc<T, SizeMax>::~hAlloc() { deallocate(); }

template <typename T, size_t SizeMax>
T* hAlloc<T, SizeMax>::operator[] (size_t i)
{
	if (i >= _num)
		return NULL;

	size_t itemId = i / sCntMax;
	size_t dataId = i % sCntMax;

	hAllocItem* item = ITEMS(itemId);
	return DATAS(dataId);
}

template <typename T, size_t SizeMax>
const T* hAlloc<T, SizeMax>::operator[] (size_t i) const
{
	if (i >= _num)
		return NULL;

	size_t itemId = i / sCntMax;
	size_t dataId = i % sCntMax;

	const hAllocItem* item = CITEMS(itemId);
	return CDATAS(dataId);
}

template<typename T, size_t SizeMax>
bool hAlloc<T, SizeMax>::allocate(size_t num)
{
	deallocate();
	if (!num)
		return true;

	size_t itemCnt = (num - 1) / sCntMax + 1;
	size_t lastItemCnt = num % sCntMax;

	items.allocate(sizeof(hAllocItem) * itemCnt);
	for (size_t i = 0; i < itemCnt; ++i)
	{
		hAllocItem* item = ITEMS(i);
		new (item) hAllocItem;

		if (i + 1 == itemCnt)
			item->allocate(sizeof(T) * lastItemCnt);
		else
			item->allocate(sSizeMax);
	}
	_num = num;
	
	return true;
}

template<typename T, size_t SizeMax>
bool hAlloc<T, SizeMax>::reallocate(size_t num)
{
	if (!num)
		deallocate();

	if (!items.size())
		return allocate(num);

	size_t itemCnt = (num - 1) / sCntMax + 1;
	size_t lastItemCnt = num % sCntMax;

	size_t oldItemCnt = items.size() / sizeof(hAllocItem);
	size_t oldLastItemCnt = ITEMS(oldItemCnt - 1)->size() / sizeof(T);

	if (oldItemCnt > itemCnt)
	{
		for (size_t cnt = itemCnt; cnt < oldItemCnt; ++cnt)
			ITEMS(cnt)->deallocate();
	}

	items.reallocate(itemCnt * sizeof(hAllocItem));

	if (oldItemCnt < itemCnt)
	{
		if (oldItemCnt)
			ITEMS(oldItemCnt - 1)->reallocate(sSizeMax);

		for (size_t cnt = oldItemCnt; cnt < itemCnt - 1; ++cnt)
			ITEMS(cnt)->allocate(sSizeMax);
	}

	ITEMS(itemCnt - 1)->reallocate(lastItemCnt * sizeof(T));
	_num = num;

	return true;
}

template<typename T, size_t SizeMax>
bool hAlloc<T, SizeMax>::deallocate()
{
	if (!items)
		return true;

	size_t itemNum = items.size() / sizeof(hAllocItem);
	for (size_t i = 0; i < itemNum; ++i)
	{
		hAllocItem* item = ITEMS(i);
		size_t dataNum = item->size() / sizeof(T);
		for (size_t j = 0; j < dataNum; ++j)
		{
			T* t = DATAS(j);
			if (!t)
				continue;

			t->~T();
		}
		item->deallocate();
	}
	items.deallocate();
	_num = 0;

	return true;
}

#undef DATAS
#undef ITEMS
#undef CDATAS
#undef CITEMS

TEST(内存分配器随机访问)
{
	hAlloc<int> a;
	a.allocate(10);
	for (size_t i = 0; i < a.size(); ++i)
		cout << a[i] << endl;
	a.deallocate();
}

template<typename T>
class hVecIterator
{
	bool _invaild = true;
	size_t _size;
public:
	hVecIterator& operator++();
	hVecIterator& operator++(int);
};

template<typename T>
hVecIterator<T>& hVecIterator<T>::operator++()
{
	
}

template<typename T>
hVecIterator<T>& hVecIterator<T>::operator++(int)
{
	// TODO: 在此处插入 return 语句
}

template <typename T>
class hVector
{
	hAlloc<T> _alloc;
	size_t _size = 0;
	size_t _capacity = 0;

	using iterator = hVecIterator<hVector<T>>;
public:
	hVector() { cout << "hVector()" << endl; }
	hVector(std::initializer_list<T> il);

	hVector(const hVector& v) { cout << "copy hVector()" << endl; }
	hVector(hVector&& v) { cout << "move hVector()" << endl; }

	size_t size() const { return _size; }
	size_t capacity() const { return _capacity; }
	bool empty() const { return !_size; }
	void clear() { resize(0); }

	void reserve(size_t num);
	template< typename... Args >
	void resize(size_t num, Args&&... args);

	void pushBack(const T& t);
	void pushBack(T&& t);
	template< typename... Args >
	T& emplaceBack(Args&&... args);

	iterator begin();
	iterator end();

	T& operator[] (size_t i) { return *_alloc[i]; }
	const T& operator[] (size_t i) const { return *_alloc[i]; }

	hVector<T>& operator=(std::initializer_list<T> il);
private:
	void checkCapacity();
};

template<typename T>
hVector<T>::hVector(std::initializer_list<T> il)
{
	reserve(il.size());

	for (auto t : il)
		emplaceBack(t);
}

template<typename T>
void hVector<T>::reserve(size_t num)
{
	if (num == _capacity)
		return;

	_capacity = num;
	if (_capacity >= _size)
	{
		_alloc.reallocate(_capacity);
		return;
	}

	for (size_t i = _capacity; i < _size; ++i)
		_alloc[i]->~T();

	_alloc.reallocate(_capacity);
}

template<typename T>
template< typename... Args >
void hVector<T>::resize(size_t num, Args&&... args)
{
	if (num == _size)
		return;

	if (num > _capacity)
	{
		_capacity = num;
		_alloc.reallocate(_capacity);
	}

	for (size_t i = num; i < _size; ++i)
		_alloc[i]->~T();

	for (size_t i = _size; i < num; ++i)
		new (_alloc[i]) T(args...);

	_size = num;
}

template <typename T>
void hVector<T>::pushBack(const T& t)
{
	checkCapacity();

	T* pT = _alloc[_size++];
	new (pT) T(t);
}

template <typename T>
void hVector<T>::pushBack(T&& t)
{
	checkCapacity();

	T* pT = _alloc[_size++];
	new (pT) T(std::move(t));
}

template<typename T>
template< typename... Args >
T& hVector<T>::emplaceBack(Args&&... args)
{
	checkCapacity();

	T* pT = _alloc[_size++];
	new (pT) T(args...);

	return *pT;
}

template<typename T>
typename hVector<T>::iterator hVector<T>::begin() 
{
	return iterator();
}

template<typename T>
typename hVector<T>::iterator hVector<T>::end()
{
	return iterator();
}

template<typename T>
hVector<T>& hVector<T>::operator=(std::initializer_list<T> il)
{
	reserve(il.size());

	for (auto t : il)
		emplaceBack(t);

	return *this;
}

template<typename T>
void hVector<T>::checkCapacity()
{
	if (_size == _capacity)
	{
		size_t add = _capacity / 2;
		if (add) _capacity += add;
		else _capacity += 1;

		_alloc.reallocate(_capacity);
	}
}

TEST(pushBack测试)
{
	hVector<int> v;
	for (int i = 0; i < 20; ++i)
	{
		v.pushBack(i);
		cout << v[i] << ":" << v.size() << "/" << v.capacity() << " ";
	}

	cout << endl;
}

class A
{
public:
	A() { cout << "A()" << endl; }
	A(const A&) { cout << "A(const A&)" << endl; }
	A(A&&) noexcept { cout << "A(A&&)" << endl; }
};

class B
{
public:
	B() { cout << "B()" << endl; }
	B(const B&) { cout << "B(const B&)" << endl; }
};

class C
{
public:
	C() { cout << "C()" << endl; }
	C(C&&) noexcept { cout << "C(C&&)" << endl; }
};

TEST(类类型pushBack测试)
{
	A a;
	hVector<A> vA;
	vA.pushBack(a);
	vA.pushBack(move(a));
	vA.pushBack(A());

	B b;
	hVector<B> vB;
	vB.pushBack(b);
	vB.pushBack(move(b));
	vB.pushBack(B());

	C c;
	hVector<C> vC;
	//vC.pushBack(c);
	vC.pushBack(move(c));
	vC.pushBack(C());
}

TEST(emplaceBack测试)
{
	hVector<int> v;
	for (int i = 0; i < 20; ++i)
	{
		v.emplaceBack(i);
		cout << v[i] << ":" << v.size() << "/" << v.capacity() << " ";
	}

	cout << endl;
}

class D
{
	int id = 0;
	string name = "";

	friend ostream& operator<<(ostream& os, const D& d);
public:
	D(int id, const string& name) : id(id), name(name) {}

};

ostream& operator<<(ostream& os, const D& d)
{
	return os << d.id << ":" << d.name;
}

TEST(类类型emplaceBack测试)
{
	hVector<D> v;
	cout << v.emplaceBack(1, "hong") << endl;
	cout << v.emplaceBack(2, "ming") << endl;
	cout << v.emplaceBack(3, "lucy") << endl;
	cout << v.emplaceBack(4, "peter") << endl;
	cout << v.emplaceBack(5, "hua") << endl;
	
	for (int i = 0; i < v.size(); ++i)
		cout << v[i] << " ";
	cout << endl;
}

TEST(resize测试)
{
	hVector<int> v1 = { 1,2,3,4,5,6,7,8,9,10 };
	cout << v1.size() << " " << v1.capacity() << endl;
	v1.resize(2);
	cout << v1.size() << " " << v1.capacity() << endl;
	v1.resize(20);
	cout << v1.size() << " " << v1.capacity() << endl;
	v1.clear();
	cout << v1.size() << " " << v1.capacity() << endl;

	vector<int> v2 = { 1,2,3,4,5,6,7,8,9,10 };
	cout << v2.size() << " " << v2.capacity() << endl;
	v2.resize(2);
	cout << v2.size() << " " << v2.capacity() << endl;
	v2.resize(20);
	cout << v2.size() << " " << v2.capacity() << endl;
	v2.clear();
	cout << v2.size() << " " << v2.capacity() << endl;
}

TEST(迭代器测试)
{
	//vector<int> v = {1,2,3};
	//
	//auto beg = v.begin();
	//cout << *beg << endl;
	//v.push_back(4);
	//++beg;
	//cout << *beg << endl;
}

class hRWLock
{
public:
	size_t rdCnt = 0;
	size_t wtCnt = 0;

	bool writing = false;

	std::mutex m;//自锁

	std::mutex rwM;//读写锁
	std::mutex wtM;//写等待锁

	std::condition_variable rdCv;
	std::condition_variable wtCv;
public:
#define LOCK std::lock_guard<std::mutex> lk(m)

	bool readLock()
	{
		{
			LOCK;
			++rdCnt;
		}
		std::unique_lock<std::mutex> lk(rwM);
		rdCv.wait(lk, [&] { LOCK; return !wtCnt; });

		return true;
	}

	bool readUnlock()
	{
		{
			LOCK;
			rdCnt -= rdCnt ? 1 : 0;
			if (wtCnt)
				wtCv.notify_one();
		}

		return true;
	}

	bool writeLock()
	{
		{
			LOCK;
			++wtCnt;

			if (rwM.try_lock())
			{
				writing = true;
				return true;
			}
		}
		std::unique_lock<std::mutex> lk(wtM);
		wtCv.wait(lk, [&]
			{
				LOCK;

				COUT_LOCK("notify");

				if (writing)
					return false;
				
				if (!rwM.try_lock())
					return false;

				writing = true;
				return true;
			});
		return true;
	}

	bool writeUnlock()
	{
		{
			LOCK;
			wtCnt -= wtCnt ? 1 : 0;
			writing = false;

			if (wtCnt)
				wtCv.notify_one();
			else if (rdCnt)
				rdCv.notify_all();
		}

		return true;
	}

#undef LOCK
};

hRWLock rwLk;
void readFunc(int i)
{

	COUT_LOCK("[" << i << "]read lock...:" << rwLk.rdCnt << " " << rwLk.wtCnt << " " << rwLk.writing);
	rwLk.readLock();
	COUT_LOCK("[" << i << "]read........:" << rwLk.rdCnt << " " << rwLk.wtCnt << " " << rwLk.writing);
	rwLk.readUnlock();
	COUT_LOCK("[" << i << "]read unlock.:" << rwLk.rdCnt << " " << rwLk.wtCnt << " " << rwLk.writing);
}

void writeFunc(int i)
{

	COUT_LOCK("[" << i << "]write lock...:" << rwLk.rdCnt << " " << rwLk.wtCnt << " " << rwLk.writing);
	rwLk.writeLock();
	//std::this_thread::sleep_for(chrono::microseconds(20));
	COUT_LOCK("[" << i << "]write........:" << rwLk.rdCnt << " " << rwLk.wtCnt << " " << rwLk.writing);
	rwLk.writeUnlock();
	COUT_LOCK("[" << i << "]write unlock.:" << rwLk.rdCnt << " " << rwLk.wtCnt << " " << rwLk.writing);

}

TEST(读写锁测试)
{
	vector<thread> rwVec;
	for (int i = 1; i <= 10; ++i)
		rwVec.emplace_back(readFunc, i);
	vector<thread> wtVec;
	for (int i = 1; i <= 10; ++i)
		wtVec.emplace_back(writeFunc, i);

	for (thread& thd : rwVec)
		thd.join();
	for (thread& thd : wtVec)
		thd.join();
}

struct AData
{
	hVector<int> v = { 1, 2, 3 };
	AData& operator=(initializer_list<int> il)
	{
		int id = 0;
		for (int i : il)
			v[id++] = i;

		return *this;
	}

};

ostream& operator<<(ostream& os, const AData& data)
{
	//for (auto i : data.v)
	//	os << i << " ";
	for (size_t i = 0; i < data.v.size(); ++i)
		os << data.v[i] << " ";

	return os;
}

struct AItem
{
	AData& data;
	//mutex m;

	AItem(AData& data) : data(data) {}

	void pData(int i)
	{
		COUT_LOCK(data);
		data = { i + 10, i + 20, i + 30 };
		COUT_LOCK(data);
	}
};

struct AMgr
{
	AData data;
	hVector<AItem> items;
	std::mutex m;
	void pData(size_t i)
	{
		size_t size = items.size();
		if (i >= size)
			items.resize(i + 1, data);

		{
			std::lock_guard<std::mutex> lk(m);
			items[i].pData(i);
		}
	}
} a;

void f(int i)
{
	a.pData(i);
}

TEST(hVector管理含互斥锁类类型)
{
	//hVector<thread> v;
	//for (int i = 0; i < 3; ++i)
	//	v.emplaceBack(f, i);
	//
	//for (int i = 0; i < v.size(); ++i)
	//	v[i].join();
	////for (auto& t : v)
	////	t.join();
}


TEST_MAIN()
