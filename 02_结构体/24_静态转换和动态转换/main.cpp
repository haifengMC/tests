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
	void _hDynamicCast(T& t, 
		decltype(dynamic_cast<const volatile void*>(static_cast<U>(NULL))) u)
	{
		t = dynamic_cast<T>((U)u);
	}

	template <typename T, typename U>
	void _hDynamicCast(...) {}
}

template <typename T, typename U>
T hDynamicCast(U u) 
{
	static_assert((std::is_pointer<T>::value && std::is_pointer<U>::value),
		"Be not pointer");

	T t = NULL;
	hDynamicDetail::_hDynamicCast<T, U>(t, u);
	return t;
}


int main()
{
	B* pB = new B;
	B* pC1 = new C;
	C* pC2 = new C;

	cout << hDynamicCast<C*>(pB) << endl;
	cout << hDynamicCast<C*>(pC1) << endl;
	cout << hDynamicCast<B*>(pC2) << endl;

	cout << typeid(decltype(dynamic_cast<B*>(
		static_cast<E*>(nullptr)))).name() << endl;

	return true;
}