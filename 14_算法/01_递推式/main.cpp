#include<iostream>
#include<cmath>
using namespace std;

uint64_t f1(uint64_t n, uint16_t i = 0)
{
	if (n == 1)
		return 0;
	return pow(2, i) * pow(n, 3) + f1(n - 1, i + 1);
}

uint64_t f(uint64_t n)
{
	if (!n)
		return 0;
	else if (1 == n)
		return 1;

	return pow(2, n - 1) + f1(n);
}

int main()
{
	uint64_t n;
	while (true)
	{
		cin >> n;
		if (1 <= n < pow(10, 9))
			cout << f(n) % 1000000007 << endl;
		else
			cout << "error" << endl;

	}

	return 0;
}