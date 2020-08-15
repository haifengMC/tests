#pragma once

#include "hSingleton.h"

namespace hTool
{
	enum class RandomType : size_t
	{
		UniformInt,		//平均分布(整数)
		UniformDeInt,	//平均分布(整数去重)
		UniformReal,	//平均分布(实数)
		Normal,			//正态分布
	};

	template <typename T>
	class hRWeight
	{
		
		size_t weight = 0;
		std::vector<T> tVec;

		size_t total = 0;
	public:
		hRWeight() {}
		hRWeight(const size_t& weight);

		bool empty() const { return tVec.empty(); }

		const size_t& getWeight() const { return weight; }
		const size_t& getTotal() const { return total; }
		const std::vector<T>& getVal() const { return tVec; }
		bool getRandVal(T* pT, size_t& idx, const size_t& randWeight);

		hRWeight& operator=(std::initializer_list<T> il);
		hRWeight& operator+=(std::initializer_list<T> il);
		hRWeight& operator+=(const hRWeight<T>& w);

		template <typename C>
		friend std::ostream& operator<<(std::ostream& os, const hRWeight<C>& w);
	};

	template <typename T>
	class hRWeightMap
	{
		size_t total = 0;
		std::map<size_t, hRWeight<T>> weights;
	public:
		const size_t& getTotal() const { return total; }
		bool getRandVal(T* pT, size_t& idx, const size_t& randWeight);

		hRWeightMap() {}
		hRWeightMap(std::initializer_list<hRWeight<T>> il) { *this = il; }
		hRWeightMap& operator=(std::initializer_list<hRWeight<T>> il);
		hRWeightMap& operator+=(std::initializer_list<hRWeight<T>> il);
		
		template <typename C>
		friend std::ostream& operator<<(std::ostream& os, const hRWeightMap<C>& w);
	};

	class hRandom : public Singleton<hRandom>
	{
		std::random_device rd; // 将用于获得随机数引擎的种子
		std::mt19937 gen; // 以 rd() 播种的标准 mersenne_twister_engine

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
		template <typename T, size_t N>
		size_t operator()(const RandomType& type, T(&buf)[N], hRWeightMap<T>& weightM);
	};
#define RANDOM hTool::hRandom::getMe()
}