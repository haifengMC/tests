#include <iostream>

using namespace std;

struct A 
{
	virtual ~A() {}
	virtual void printMe() { cout << "A" << endl; }
};

template <size_t N>
A* factor() { return new A(); }
template <size_t N>
void printMe()
{
	A* pA = factor<N>();

	cout << N << ":" << pA << endl;
	if (pA)
		pA->printMe();

	delete pA;
}

struct B :public A
{
	void printMe() { cout << "B" << endl; }
};
template <>
A* factor<1>() { return new B(); }

int main()
{
	printMe<0>();
	printMe<1>();

	return 0;
}