#include <chrono>
#include <initializer_list>
#include <sstream>
#include <iostream>

using namespace std;

struct A
{
	size_t _i = 0;

	constexpr A(size_t i) { _i = i; }
};

constexpr A operator"" _sA(size_t i)
{
	return A(i);
}

int main()
{
	A a = 1_sA;
	cout << a._i << endl;

	return 0;
}