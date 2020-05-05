#include <random>
#include <iostream>

int main()
{
	std::random_device rd;  // 将用于获得随机数引擎的种子
	std::mt19937 gen(rd()); // 以 rd() 播种的标准 mersenne_twister_engine
	std::uniform_real_distribution<> dis(0, 1);
	for (int n = 0; n < 10; ++n) {
		// 用 dis 变换 gen 生成的随机 unsigned int 为 [1, 2) 中的 double
		std::cout << dis(gen) << ' '; // 每次调用 dis(gen) 都生成新的随机 double
	}
	std::cout << '\n';
}