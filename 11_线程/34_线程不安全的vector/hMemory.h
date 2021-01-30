#pragma once

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

