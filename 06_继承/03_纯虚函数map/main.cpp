#include <iostream>
#include <map>

using namespace std;

class A
{
public:
	virtual ~A() {}
	virtual int getId() { return 0; }
};

class B : public A
{
	int i;
public:
	B(int i) : i(i) {}
	virtual int getId() { return i; }
};


int main()
{
	map<int, A> m;
	


	return 0;
}