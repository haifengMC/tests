#include <iostream>

using namespace std;


template <typename Ty>
void callFunc(Ty& t)
{
	if (std::is_member_function_pointer<decltype(&Ty::f)>::value)
		cout << "true" << endl;
	else
		cout << "false" << endl;
}


struct A { void f() { cout << "A::f()" << endl; } };
struct B { void f() { cout << "B::f()" << endl; } };
struct C { void k() { cout << "C::k()" << endl; } };

int main()
{
	A a;
	callFunc(a);
	C c;
	callFunc(c);
	return 0;
}