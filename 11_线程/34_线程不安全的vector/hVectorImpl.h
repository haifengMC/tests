#pragma once

template<typename T>
hVecIterator<T>& hVecIterator<T>::operator++()
{

}

template<typename T>
hVecIterator<T>& hVecIterator<T>::operator++(int)
{
	// TODO: 在此处插入 return 语句
}

template<typename T>
hVector<T>::hVector(std::initializer_list<T> il)
{
	reserve(il.size());

	for (auto t : il)
		emplaceBack(t);
}

template<typename T>
hVector<T>::hVector(const hVector<T>& v)
{
	_alloc = v._alloc;
	_size = v._size;
	_capacity = v._capacity;
}

template<typename T>
hVector<T>::hVector(hVector<T>&& v) : lk(v.lk), _alloc(std::move(v._alloc))
{
	_size = v._size;
	_capacity = v._capacity;
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