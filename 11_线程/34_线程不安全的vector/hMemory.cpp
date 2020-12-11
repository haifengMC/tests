#include "global.h"
#include "hMemory.h"

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