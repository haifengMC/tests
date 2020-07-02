#include <iostream>

using namespace std;

class B
{
public:
	int b;
};

class A : public B
{
public:
	int a;
};

int main()
{
	A a;
	cout << a.a << a.b << endl;

	return 0;
}