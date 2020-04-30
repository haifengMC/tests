#include <iostream>

using namespace std;

class A
{
public:
	int a;
	A() : a(0) {}
};

class B : public A
{
public:
	B() {}
	void printA() { cout << a << endl; }
};

class C : public B
{
public:
};


int main()
{
	B b;
	b.printA();
	C c;
	

	return 0;
}