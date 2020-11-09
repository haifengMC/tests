#include <iostream>

using namespace std;

struct Base
{
	void func() { pt(); }
	virtual void pt() { cout << "Base" << endl; }
};

struct A : public Base
{
	void pt() { cout << "A" << endl; }
};

struct B : public Base
{
	void pt() { cout << "B" << endl; }
};

int main()
{
	Base* arr[3];
	arr[0] = new Base();
	arr[1] = new A();
	arr[2] = new B();

	for (Base* pBase : arr)
		pBase->func();
	for (Base* pBase : arr)
		delete pBase;

	return 0;
}