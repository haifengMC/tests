#include "hRandom.h"
#pragma once

namespace hTool
{
	template <typename T>
	hRWeight<T>::hRWeight(const size_t& weight) : weight(weight) {}

	template<typename T>
	bool hRWeight<T>::getRandVal(T* pT, size_t& idx, const size_t& randWeight)
	{
		if (randWeight >= total)
			return false;

		size_t randId = randWeight / weight;
		pT[idx++] = tVec[randId];
		std::swap(tVec[randId], tVec.back());
		tVec.pop_back();
		total = total < weight ? 0 : total - weight;

		return true;
	}

	template<typename T>
	hRWeight<T>& hRWeight<T>::operator=(std::initializer_list<T> il)
	{
		tVec = il;
		total = weight * il.size();

		return *this;
	}

	template<typename T>
	hRWeight<T>& hRWeight<T>::operator+=(std::initializer_list<T> il)
	{
		for (auto& t : il)
			tVec.push_back(t);

		total += weight * il.size();

		return *this;
	}

	template<typename T>
	hRWeight<T>& hRWeight<T>::operator+=(const hRWeight<T>& w)
	{
		if (!weight)
			weight = w.getWeight();

		if (weight != w.getWeight())
			return *this;

		total += w.getTotal();

		for (auto& t : w.getVal())
			tVec.push_back(t);

		return *this;
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const hRWeight<T>& w)
	{
		os << "[" << w.weight << "]";
		bool first = true;
		for (auto& t : w.tVec)
		{
			if (first) first = false;
			else os << " ";
			os << t;
		}
		return os;
	}

	template<typename T>
	bool hRWeightMap<T>::getRandVal(T* pT, size_t& idx, const size_t& randWeight)
	{
		if (!pT || randWeight >= total)
			return false;

		size_t tmpWeight = 0;
		for (typename std::map<size_t, hRWeight<T>>::iterator itWeight = weights.begin(); 
			itWeight != weights.end();
			itWeight->second.empty() ? itWeight = weights.erase(itWeight) : ++itWeight)
		{
			hRWeight<T>& weight = itWeight->second;
			
			if (randWeight >= tmpWeight + weight.getTotal())
			{
				tmpWeight += weight.getTotal();
				continue;
			}
			
			bool ret = weight.getRandVal(pT, idx, randWeight - tmpWeight);
			if (ret)
			{
				total -= weight.getWeight();
				if (weight.empty())
					weights.erase(itWeight);
			}

			return ret;
		}

		return false;
	}

	template <typename T>
	hRWeightMap<T>& hRWeightMap<T>::operator=(std::initializer_list<hRWeight<T>> il)
	{
		total = 0;
		weights.clear();

		return *this += il;
	}

	template <typename T>
	hRWeightMap<T>& hRWeightMap<T>::operator+=(std::initializer_list<hRWeight<T>> il)
	{
		for (auto& w : il)
		{
			weights[w.getWeight()] += w;
			total += w.getTotal();
		}

		return *this;
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const hRWeightMap<T>& w)
	{
		os << "{";
		bool first = true;
		for (auto& t : w.weights)
		{
			if (first) first = false;
			else os << ", ";
			os << t.second;
		}
		return os << "}";
	}

	template <typename T>
	size_t hRandom::operator()(const RandomType& type, T* buf, size_t n, const double& min, const double& max)
	{
		switch (type)
		{
		case RandomType::UniformInt:
			{
				typename std::uniform_int<>::param_type param(min, max);
				uniformInt.param(param);
				for (size_t i = 0; i < n; ++i)
					buf[i] = uniformInt(gen);
			}
			break;
		case RandomType::UniformReal:
			{
				typename std::uniform_real<>::param_type param(min, max);
				uniformReal.param(param);
				for (size_t i = 0; i < n; ++i)
					buf[i] = uniformReal(gen);
			}
			break;
		case RandomType::Normal:
		{
			typename std::normal_distribution<>::param_type param(min, max);
			normal.param(param);
			for (size_t i = 0; i < n; ++i)
				buf[i] = normal(gen);
		}
		break;
		default:
			break;
		}

		return n;
	}

	template <typename T, size_t N>
	size_t hRandom::operator()(const RandomType& type, T(&buf)[N], const double& min, const double& max)
	{
		return this->operator()(type, buf, N, min, max);
	}

	template <typename T>
	size_t hRandom::operator()(const RandomType& type, T* buf, size_t bufN, hRWeightMap<T>& weightM)
	{
		switch (type)
		{
		case RandomType::UniformDeInt:
		{
			if (!buf || !bufN || !weightM.getTotal())
				return 0;

			size_t ret = 0;
			for (size_t i = 0; i < bufN; ++i)
			{
				size_t total = weightM.getTotal() ? weightM.getTotal() - 1 : 0;
				typename std::uniform_int<>::param_type param(0, total);
				uniformInt.param(param);

				size_t randWeight = uniformInt(gen);
				if (!weightM.getRandVal(buf, ret, randWeight))
					return ret;
			}
			return ret;
		}
		break;
		default:
			break;
		}
	}
	template<typename T, size_t N>
	inline size_t hRandom::operator()(const RandomType& type, T(&buf)[N], hRWeightMap<T>& weightM)
	{
		return this->operator()(type, buf, N, weightM);
	}
}