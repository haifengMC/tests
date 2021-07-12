#include <iostream>
#include <functional>

using namespace std;


template <typename Ty>
struct CallFunc
{
	template <typename Ty, typename Func>
	void operator() (Ty& t, Func) { cout << "Ty::void" << endl; }
	template <typename Ty>
	void operator() (Ty& t, void(Ty::* f)() = &Ty::f) { cout << "Ty::f" << endl; }
};


struct A { void f() { cout << "A::f()" << endl; } };
struct B { void f() { cout << "B::f()" << endl; } };
struct C { void k() { cout << "C::k()" << endl; } };

int main()
{
	A a;
	CallFunc<A>()(a, &A::f);
	B b;
	CallFunc<B>()(b, &A::f);
	C c;
	CallFunc<C>()(c, &A::f);
	return 0;
}