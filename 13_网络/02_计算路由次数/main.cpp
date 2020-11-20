#include <iostream>

using namespace std;

uint64_t pow(size_t n, size_t i)
{
	if (!i || !n) return 1;

	return n * pow(n, i - 1);
}

uint64_t calcRoute(size_t n, size_t i)
{
	if (!i || !n) return 0;
	return 1 + n * (pow(n - 1, i - 1) - 1);
}

int main()
{
	cout << pow(0, 1) << " " << pow(0, 10) << endl;
	cout << pow(1, 1) << " " << pow(1, 10) << endl;
	cout << pow(2, 1) << " " << pow(2, 10) << endl;

	size_t n = 0, i = 0;
	while (cin >> n >> i)
		cout << calcRoute(n, i) << endl;

	return 0;
}