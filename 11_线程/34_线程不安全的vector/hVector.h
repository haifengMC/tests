#pragma once

template<typename T>
class hVecIterator;
template <typename T>
class hVector
{
	hAlloc<T> _alloc;
	size_t _size = 0;
	size_t _capacity = 0;

	hVector<T>** _pCont = new hVector<T>*(this);
public:
	using iterator = hVecIterator<T>;

	hVector() {}
	hVector(std::initializer_list<T> il);

	hVector(const hVector& v);
	hVector(hVector&& v);
	~hVector() { DEL(_pCont); }

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
	void rstPThis();
	void checkCapacity();
};

template<typename T>
class hVecIterator
{
	size_t _size = 0;
	hVector<T>** _cont = NULL;
public:
	hVecIterator() {}
	hVecIterator(size_t n, hVector<T>** cont) : _size(n), _cont(cont) {}

	bool operator==(const hVecIterator& it);
	bool operator!=(const hVecIterator& it);
	T& operator*();
	hVecIterator& operator++();
	hVecIterator operator++(int);
private:
	void vertify();
	void vertifyRange();
	void vertifySame(const hVecIterator& it);
};