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
	template <typename T, bool TBool, typename U, bool UBool>
	struct _hDynamicCast
	{
		static T dynamic(U u) 
		{ 
			static_assert((std::is_pointer<T>::value && std::is_pointer<U>::value),
				"Be not pointer");

			return NULL; 
		}
	};

	template <typename T, typename U>
	struct _hDynamicCast<T, true, U, true>
	{
		static T dynamic(U u) { return dynamic_cast<T>((U)u); }
	};
}

template <typename T, typename U>
T hDynamicCast(U u) 
{
	return hDynamicDetail::_hDynamicCast<
		T, is_polymorphic<remove_pointer<remove_reference<T>::type>::type>::value,
		U, is_polymorphic<remove_pointer<remove_reference<U>::type>::type>::value>::
		dynamic(u);
}


int main()
{
	int* pI = new int(0);
	A* pA = new A;
	B* pB = new B;
	B* pC1 = new C;
	C* pC2 = new C;
	D* pD = new D;
	E* pE = new E;
	
	cout << hDynamicCast<B*>(pI) << endl;
	cout << hDynamicCast<B*>(pA) << endl;
	cout << hDynamicCast<B*>(pB) << endl;
	cout << hDynamicCast<C*>(pB) << endl;
	cout << hDynamicCast<C*>(pC1) << endl;
	cout << hDynamicCast<B*>(pC2) << endl;
	cout << hDynamicCast<B*>(pD) << endl;
	cout << hDynamicCast<B*>(pE) << endl;



	return true;
}