#pragma once

template<typename T>
class hVecIterator
{
	bool _invaild = true;
	size_t _size;
public:
	hVecIterator& operator++();
	hVecIterator& operator++(int);
};

template <typename T>
class hVector
{
	hAlloc<T> _alloc;
	size_t _size = 0;
	size_t _capacity = 0;

	hRWLock* lk = new hRWLock;

	using iterator = hVecIterator<hVector<T>>;
public:
	hVector() {}
	hVector(std::initializer_list<T> il);

	hVector(const hVector& v);
	hVector(hVector&& v);
	~hVector() { delete lk; }

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