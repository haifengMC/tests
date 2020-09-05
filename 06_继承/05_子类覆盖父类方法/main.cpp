#include <iostream>
#include <map>

using namespace std;

class A
{
public:
	virtual void func1() { cout << "A1" << endl; }
	void func2() { cout << "A2" << endl; }
};

class B : public A
{
public:
	void func1() { A::func1(); cout << "B1" << endl; }
	void func2() { A::func2(); cout << "B2" << endl; }
};

int main()
{
	A* pa = new B;
	pa->func1();
	pa->func2();

	return 0;
}