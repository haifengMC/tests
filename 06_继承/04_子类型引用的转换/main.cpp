#include <iostream>

using namespace std;

class A
{
public:
	A() {}
	virtual void pt() const { cout << "A" << endl; }
};

class B1 : public A
{
	int i;
public:
	B1(int i) : i(i) {}
	virtual void pt() const { cout << "B1" << " " << i << endl; }
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

	return 0;
}