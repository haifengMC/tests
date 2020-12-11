#pragma once

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

