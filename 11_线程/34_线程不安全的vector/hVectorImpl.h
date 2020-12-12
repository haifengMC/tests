#include "hVector.h"
#pragma once

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
hVector<T>::hVector(hVector<T>&& v) : _alloc(std::move(v._alloc))
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

	rstPThis();
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

	rstPThis();
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
	rstPThis();

	T* pT = _alloc[_size++];
	new (pT) T(t);
}

template <typename T>
void hVector<T>::pushBack(T&& t)
{
	checkCapacity();
	rstPThis();

	T* pT = _alloc[_size++];
	new (pT) T(std::move(t));
}

template<typename T>
template< typename... Args >
T& hVector<T>::emplaceBack(Args&&... args)
{
	checkCapacity();
	rstPThis();

	T* pT = _alloc[_size++];
	new (pT) T(args...);

	return *pT;
}

template<typename T>
typename hVector<T>::iterator hVector<T>::begin()
{
	return iterator(0, _pCont);
}

template<typename T>
typename hVector<T>::iterator hVector<T>::end()
{
	return iterator(_size, _pCont);
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
void hVector<T>::rstPThis()
{
	hVector<T>** tmp = new hVector<T> *(this);
	*_pCont = NULL;
	DEL(_pCont);
	_pCont = tmp;
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

template<typename T>
bool hVecIterator<T>::operator==(const hVecIterator& it)
{
	vertifySame(it);
	return _size == it._size;
}

template<typename T>
bool hVecIterator<T>::operator!=(const hVecIterator& it)
{
	vertifySame(it);
	return _size != it._size;
}


template<typename T>
T& hVecIterator<T>::operator*()
{
	vertifyRange();
	return (**_cont)[_size];
}

template<typename T>
hVecIterator<T>& hVecIterator<T>::operator++()
{
	vertifyRange();
	++_size;
	return *this;
}

template<typename T>
hVecIterator<T> hVecIterator<T>::operator++(int)
{
	hVecIterator<T> tmp = *this;
	++* this;
	return tmp;
}

template<typename T>
void hVecIterator<T>::vertify()
{
	if (!_cont)
		throw std::invalid_argument("操作未知容器");

	if (!*_cont)
		throw std::domain_error("迭代器失效");
}

template<typename T>
void hVecIterator<T>::vertifyRange()
{
	vertify();

	if ((*_cont)->size() <= _size)
		throw std::range_error("迭代器越界");
}

template<typename T>
void hVecIterator<T>::vertifySame(const hVecIterator& it)
{
	vertify();

	if (*_cont != *it._cont)
		throw std::invalid_argument("迭代器来自不同容器");
}
