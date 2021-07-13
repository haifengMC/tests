#include <iostream>

using namespace std;

namespace hCallFuncDetail
{
	template <typename Base, bool isBase>
	struct _hCallFunc
	{
		template <typename Func, typename Ty>
		static void exec(Func, Ty&) {}
	};

	template <typename Base>
	struct _hCallFunc<Base, true>
	{
		template <typename Func, typename Ty>
		static void exec(Func f, Ty& t) { return f(t); }
	};
}

template <typename Base>
struct hCallFunc
{
	template <typename Func, typename Ty>
	static void exec(Func f, Ty& t)
	{ 
		hCallFuncDetail::_hCallFunc<Base, std::is_base_of_v<Base, Ty>>::exec(f, t);
	}
};

struct Base { virtual void f() { cout << "Base::f()" << endl; } };
struct A : public Base { void f() { cout << "A::f()" << endl; } };
struct B { void f() { cout << "B::f()" << endl; } };
struct C : public Base { void k() { cout << "C::k()" << endl; } };
void f(Base& b) { b.f(); }
template <typename Ty>
void callBaseF(Ty t) { hCallFunc<Base>::exec(f, t); }

int main()
{
	cout << "exec(a)" << endl;
	callBaseF(A());
	cout << "exec(b)" << endl;
	callBaseF(B());
	cout << "exec(c)" << endl;
	callBaseF(C());

	return 0;
}