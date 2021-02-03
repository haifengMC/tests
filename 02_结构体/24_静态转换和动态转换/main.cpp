#include <iostream>
#include <type_traits>
#include <typeinfo>

using namespace std;

struct A {};
struct B { virtual ~B() {} };
struct C : public B {};
struct D { virtual ~D() {} };
struct E : public D {};


namespace hDynamicDetail
{
	template <typename T, typename U>
	T _hDynamicCast(decltype(dynamic_cast<T>(
		static_cast<U>(NULL))) u)
	{
		return dynamic_cast<T>((U)u);
	}

	template <typename T, typename U>
	T _hDynamicCast(...)
	{
		static_assert((std::is_pointer<T>::value && std::is_pointer<U>::value) ||
			(std::is_reference<T>::value && std::is_reference<U>::value),
			"Be not pointer or reference");

		return NULL;
	}
}

template <typename T, typename U>
T hDynamicCast(U u) { return hDynamicDetail::_hDynamicCast<T, U>(u); }

int main()
{
	A* pA = new A;
	B* pB = new B;
	C* pC = new C;
	D* pD = new D;
	E* pE = new E;
	cout << hDynamicCast<B*>(pA) << endl;
	cout << hDynamicCast<B*>(pB) << endl;
	cout << hDynamicCast<B*>(pC) << endl;
	cout << hDynamicCast<B*>(pD) << endl;
	cout << hDynamicCast<B*>(pE) << endl;

	cout << typeid(decltype(dynamic_cast<B*>(
		static_cast<E*>(nullptr)))).name() << endl;

	return true;
}