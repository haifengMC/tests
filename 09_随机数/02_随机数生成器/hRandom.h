#pragma once

#include "hSingleton.h"

namespace hTool
{
	enum class RandomType : size_t
	{
		UniformInt,		//ƽ���ֲ�(����)
		UniformIntDe,	//ƽ���ֲ�(����ȥ��)
		UniformReal,	//ƽ���ֲ�(ʵ��)
		Normal,			//��̬�ֲ�
	};

	template <typename T>
	class hRWeight
	{
		
		const size_t weight;
		std::vector<T> tVec;

		size_t total = 0;
	public:
		hRWeight(const size_t& weight);

		size_t& getTotal() const { return total; }
		bool getRandVal(T* pT, size_t& idx, const size_t& randWeight);
	};

	template <typename T>
	class hRWeightMap
	{
		size_t total = 0;
		std::map<size_t, hRWeight> weights;
	public:
		size_t& getTotal() const { return total; }
		bool getRandVal(T* pT, size_t& idx, const size_t& randWeight);
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
		template <typename T>
		size_t operator()(const RandomType& type, T* buf, size_t bufN, hRWeightMap<T>& weightM);
	};
#define RANDOM hTool::hRandom::getMe()
}