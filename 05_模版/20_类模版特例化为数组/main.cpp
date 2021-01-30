#include <iostream>
#include <typeinfo>
#include <type_traits>

using namespace std;

template<typename T>
struct A
{
	static void f(const T& t) { cout << typeid(T).name() << ":T" << endl; }
};

template<typename T, size_t N>
struct A<T[N]>
{
	static void f(const T(&t)[N]) { cout << "T[N]" << N << endl; }
};

int main()
{
	int i1[5];
	A<decltype(i1)>::f(i1);
	const int i2[5] = {};
	A<decltype(i2)>::f(i2);
	return 0;
}