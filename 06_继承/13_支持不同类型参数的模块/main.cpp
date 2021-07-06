#include <iostream>

using namespace std;

struct A
{
	int i1 = 1;
	int i2 = 2;
};

struct B
{
	int i1 = 3;
	int i2 = 4;
};

struct FuncBase { virtual void printCallback() = 0; };

template <typename T>
struct PrintFunc : public FuncBase
{
	void printCallback() { printIt(T()); }
	virtual void printIt(const T& a) = 0;
};

struct FuncA : public PrintFunc<A> { void printIt(const A& a) { cout << "A " << a.i1 << "," << a.i2 << endl; } };
struct FuncB : public PrintFunc<B> { void printIt(const B& b) { cout << "B " << b.i1 << "," << b.i2 << endl; } };

int main()
{
	FuncBase* FuncArr[] = { new FuncA, new FuncB };
	for (auto pFunc : FuncArr)
	{
		pFunc->printCallback();
		delete pFunc;
	}

	return 0;
}