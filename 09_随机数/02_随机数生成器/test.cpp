#include "global.h"
#include "hSingleton.h"
#include "hTest.h"
#include "hRandom.h"
#include "hRandomImpl.h"
#include "test.h"

TEST_INIT(Tst, testAll)

template <typename T, size_t N>
void printRand(T (&randNum)[N])
{
	std::map<T, size_t> statistic;
	for (const T& t : randNum)
		++statistic[t];

	for (const auto& s : statistic)
	{
		std::cout << "[" << s.first << "]\t" << std::string(200 * s.second / N, '*') << std::endl;
	}
}

TEST(Tst, Tst1)
{
	size_t randNum[20000] = {};
	//hTool::hRandom::getMe().operator()<size_t>(hTool::RandomType::UniformInt, randNum, 1, 10);
	//hTool::hRandom::getMe()(hTool::RandomType::UniformInt, randNum, 1, 10);
	RANDOM(hTool::RandomType::UniformInt, randNum, 1, 10);
	printRand(randNum);
}

TEST(Tst, Tst2)
{
	int randNum[20000] = {};
	//hTool::hRandom::getMe().operator()<size_t>(hTool::RandomType::UniformInt, randNum, 1, 10);
	//hTool::hRandom::getMe()(hTool::RandomType::UniformInt, randNum, 1, 10);
	RANDOM(hTool::RandomType::Normal, randNum, 1, 6);
	printRand(randNum);
}

TEST(Tst, Tst3)
{
	int i = 0;
	for (size_t n = 20; n > 0; --n)
	{
		RANDOM(hTool::RandomType::UniformInt, &i, 1, 1, n);
		std::cout << i << " ";
	}
	std::cout << std::endl;
}