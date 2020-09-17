#include <iostream>
#include <map>
#include "hAutoPtr.h"
#include "hAutoPtrImpl.h"

using namespace std;
using namespace hTool;

class A 
{
	int i = 0;
public:
	A(int i) : i(i) {}

	void printA() { cout << "A" << i << endl; }
};
class B
{
	int i = 0;
public:
	B(int i) : i(i) {}

	void printB() { cout << "B" << i << endl; }
};

class C
{
	hAutoPtr<A> a;
	hAutoPtr<B> b;

public:
	C() { a.emplace(1); b.emplace(2); }
};

int main()
{
	{
		hAutoPtr<A> a1;
		a1.emplace(10);
		if (a1) 
			a1->printA();

		hAutoPtr<A> a2;
		a2 = a1;

		hAutoPtr<A> a3 = a1;

		hAutoPtr<A> a4 = move(a1);

		a1 = move(a4);
		a4.emplace(20);
		a2 = a4;

		C c;
	}
	//hAutoPtr<A> a2(1);

	{
		
	}

	cout << "³ÌÐò½áÊø" << endl;
	return 0;
}