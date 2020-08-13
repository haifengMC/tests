#include "hRandom.h"
#pragma once

namespace hTool
{
	template <typename T>
	hRWeight<T>::hRWeight(const size_t& weight) : weight(weight) {}

	template<typename T>
	bool hRWeight<T>::getRandVal(T* pT, size_t& idx, const size_t& randWeight)
	{
		size_t randId = randWeight / weight;
	}

	template<typename T>
	bool hRWeightMap<T>::getRandVal(T* pT, size_t& idx, const size_t& randWeight)
	{
		if (!pT || randWeight >= total)
			return false;

		size_t tmpWeight = 0;
		for (auto& pairWeight : weights)
		{
			hRWeight& weight = pairWeight.second;
			if (randWeight < tmpWeight + weight.getTotal())
				return weight.getRandVal(pT, idx, randWeight - tmpWeight);

			tmpWeight += weight.getTotal();
		}

		return false;
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
		case RandomType::UniformIntDe:
		{
			if (!buf || !bufN || weightM.empty())
				return 0;

			size_t ret = 0;
			size_t weightEndN = weightN - 1;

			for (size_t i = 0; i < bufN; ++i)
			{
				if (!weightEndN)
				{
					buf[ret++] = weight[weightEndN].id;
					break;
				}

				size_t total = weightM.getTotal() ? weightM.getTotal() - 1 : 0;
				typename std::uniform_int<>::param_type param(0, total);
				uniformInt.param(param);

				size_t randWeight = uniformInt(gen);
				size_t tmpWeight = 0;
				for (size_t j = 0; j < weightN; ++j)
				{
					if (tmpWeight + weight[j].weight >= randWeight)
					{
						buf[ret++] = weight[j].id;
						totalWeight -= weight[j].weight;

						std::swap(weight[j].id, weight[weightEndN].id);
						std::swap(weight[j].weight, weight[weightEndN].weight);

						if (weightEndN)
							--weightEndN;

						break;
					}
					tmpWeight += weight[j].weight;
				}
			}
			
		}
		break;
		default:
			break;
		}
	}
}