#include <random>
#include <iostream>

int main()
{
	std::random_device rd;  // �����ڻ����������������
	std::mt19937 gen(rd()); // �� rd() ���ֵı�׼ mersenne_twister_engine
	std::uniform_real_distribution<> dis(0, 1);
	for (int n = 0; n < 10; ++n) {
		// �� dis �任 gen ���ɵ���� unsigned int Ϊ [1, 2) �е� double
		std::cout << dis(gen) << ' '; // ÿ�ε��� dis(gen) �������µ���� double
	}
	std::cout << '\n';
}