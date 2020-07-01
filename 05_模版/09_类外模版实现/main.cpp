#include <iostream>

using namespace std;

class A
{
public:
	A() {}

	template<typename T>
	void func(T a);
};
template<typename T>
void A::func(T a) { cout << a << endl; }


int main()
{
	A a;
	a.func(1);
}