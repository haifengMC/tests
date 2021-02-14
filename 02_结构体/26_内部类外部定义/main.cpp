#include <iostream>

using namespace std;

class A
{
	class B;
public:
	A();

};

class A::B
{
public:
	B() { cout << "B" << endl; }
};

int main()
{
	A a;
	return 0;
}