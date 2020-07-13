#pragma once

namespace hTool
{
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
}