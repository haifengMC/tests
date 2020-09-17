#pragma once

namespace hTool
{
	template <typename T>
	std::map<T*, size_t*> hAutoPtr<T>::pTMap;

	template<typename T>
	hAutoPtr<T>::hAutoPtr() {}

	template<typename T>
	hAutoPtr<T>::~hAutoPtr() { destory(); }

	template<typename T>
	hAutoPtr<T>::hAutoPtr(const hAutoPtr& ap) { copy(ap); }

	template<typename T>
	hAutoPtr<T>::hAutoPtr(hAutoPtr&& ap) { move(std::move(ap)); }

	template<typename T>
	hAutoPtr<T>& hAutoPtr<T>::operator=(const hAutoPtr& ap)
	{
		if (pT == ap.pT)
			return *this;
		destory();
		copy(ap);

		return *this;
	}

	template<typename T>
	hAutoPtr<T>& hAutoPtr<T>::operator=(hAutoPtr&& ap)
	{
		if (!pT)
			destory();
		move(std::move(ap));

		return *this;
	}

	template<typename T>
	void hAutoPtr<T>::bind(T* pT)
	{
		if (!pT)
			return;

		if (pT == this->pT)
			return;

		destory();

		this->pT = pT;

		auto it = pTMap.find(pT);
		if (it == pTMap.end())
		{
			num = new size_t(0);
			pTMap.insert(std::make_pair(pT, num));

		}
		else
		{
			num = it->second;
			++* num;
		}
	}

	template<typename T>
	template<typename... Args>
	void hAutoPtr<T>::emplace(Args... args)
	{
		destory();

		num = new size_t(0);
		pT = new T(args...);
		pTMap.insert(std::make_pair(pT, num));
	}

	template<typename T>
	hAutoPtr<T>::operator bool () const
	{
		return pT;
	}

	template<typename T>
	T* hAutoPtr<T>::operator->() {
		if (!pT)
			abort();

		return pT;
	}

	template<typename T>
	void hAutoPtr<T>::copy(const hAutoPtr& ap)
	{
		pT = ap.pT;
		num = ap.num;
		++* num;
	}

	template<typename T>
	void hAutoPtr<T>::move(hAutoPtr&& ap)
	{
		pT = ap.pT;
		num = ap.num;
		ap.pT = NULL;
		ap.num = NULL;
	}

	template<typename T>
	void hAutoPtr<T>::destory()
	{
		if (num && *num)
		{
			--* num;
			return;
		}

		if (pT)
		{
			delete pT;
			pTMap.erase(pT);
			pT = NULL;
		}

		if (num)
		{
			delete num;
			num = NULL;
		}
	}
}
