#include <iostream>

using namespace std;

enum
{
	Type_None,
	Type_A1,
	Type_A2,
};

struct A 
{
	virtual ~A() {}
	virtual void printMe() = 0;
};

template <size_t N>
A* factory() { return NULL; }
template <size_t N>
void printA()
{
	A* pA = factory<N>();

	cout << N << ":" << pA << endl;
	if (pA)
		pA->printMe();

	delete pA;
}

struct A1 :public A
{
	void printMe() { cout << "A1" << endl; }
};
template <>
A* factory<Type_A1>() { return new A1(); }

struct A2 :public A
{
	void printMe() { cout << "A2" << endl; }
};
template <>
A* factory<Type_A2>() { return new A2(); }

int main()
{
	printA<Type_None>();
	printA<Type_A1>();
	printA<Type_A2>();

	return 0;
}