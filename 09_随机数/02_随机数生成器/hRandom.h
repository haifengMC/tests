#pragma once

#include "hSingleton.h"

namespace hTool
{
	enum class RandomType : size_t
	{
		UniformInt,		//ƽ���ֲ�(����)
		UniformReal,	//ƽ���ֲ�(ʵ��)
		Normal,			//��̬�ֲ�
	};

	class hRandom : public Singleton<hRandom>
	{
		std::random_device rd; // �����ڻ����������������
		std::mt19937 gen; // �� rd() ���ֵı�׼ mersenne_twister_engine

		std::uniform_int_distribution<> uniformInt;
		std::uniform_real_distribution<> uniformReal;
		std::normal_distribution<> normal;
	public:
		hRandom();

		template <typename T>
		size_t operator()(const RandomType& type, T* buf, size_t n, const double& min, const double& max);
		template <typename T, size_t N>
		size_t operator()(const RandomType& type, T (&buf)[N], const double& min, const double& max);
	};
#define RANDOM hTool::hRandom::getMe()
}