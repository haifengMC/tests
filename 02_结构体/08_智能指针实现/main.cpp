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
	hAutoPtr<A> a1;
	hAutoPtr<A> a2;

public:
	B() { a1.emplace(1); a2.emplace(2); }
};

int main()
{
	{
		hAutoPtr<A> a1;
		a1.emplace(10);
		a1->printA();

		hAutoPtr<A> a2;
		a2 = a1;

		hAutoPtr<A> a3 = a1;

		hAutoPtr<A> a4 = move(a1);

		a1 = move(a4);
		a4.emplace(20);
		a2 = a4;
	}
	//hAutoPtr<A> a2(1);

	{
		B b;
	}

	cout << "³ÌÐò½áÊø" << endl;
	return 0;
}