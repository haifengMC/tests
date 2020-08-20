#include <iostream>

using namespace std;

class A
{
public:
	A() {}
	virtual void pt() const { cout << "A" << endl; }
};

ostream& operator<<(ostream& os, const A& a)
{
	a.pt();
	return os;
}

class B1 : public A
{
	int i;
public:
	B1(int i) : i(i) {}
	virtual void pt() const { cout << "B1" << " " << i << endl; }
};

class C
{
public:
	virtual ~C() {}

};


int main()
{
	A* a1 = new B1(2);
	A* a2 = dynamic_cast<const B1*>(a1) ? new B1(dynamic_cast<const B1&>(*a1)) : NULL;
	a1->pt();
	a2->pt();

	A a3;
	cout << dynamic_cast<B1*>(&a3) << endl;

	B1 b1(3);
	cout << dynamic_cast<A&>(b1) << endl;

	C c;
	try
	{
		dynamic_cast<const A&>(c);
	}
	catch (bad_cast e)
	{
		cout << "ERR" << endl;
	}

	return 0;
}