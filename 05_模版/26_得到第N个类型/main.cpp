#include <map>
#include <iostream>
#include <ratio>
#include <typeinfo>
#include <type_traits>

template <size_t N, class...> 
struct GetNType { using Type = void; };
template<typename First, typename... _Rest>
struct GetNType<1, First, _Rest...> { using Type = First; };
template<size_t N, typename FirstTy, typename... _Rest>
struct GetNType <N, FirstTy, _Rest...> : public GetNType<std::ratio_subtract<std::ratio<N>, std::ratio<1>>::num, _Rest...> {};

class A {};

#define Alias
#ifdef Alias
template <size_t N, typename... _Ty>
using SubType = typename GetNType<N, _Ty...>::Type;
#endif

int main()
{
	using namespace std;
	cout << typeid(GetNType<0, int, char, float, A>::Type).name() << endl;
	cout << typeid(GetNType<1, int, char, float, A>::Type).name() << endl;
	cout << typeid(GetNType<2, int, char, float, A>::Type).name() << endl;
	cout << typeid(GetNType<3, int, char, float, A>::Type).name() << endl;
	cout << typeid(GetNType<4, int, char, float, A>::Type).name() << endl;
	cout << typeid(GetNType<5, int, char, float, A>::Type).name() << endl;
	cout << endl;
#ifdef Alias
	cout << typeid(SubType<0, int, char, float, A>).name() << endl;
	cout << typeid(SubType<1, int, char, float, A>).name() << endl;
	cout << typeid(SubType<2, int, char, float, A>).name() << endl;
	cout << typeid(SubType<3, int, char, float, A>).name() << endl;
	cout << typeid(SubType<4, int, char, float, A>).name() << endl;
	cout << typeid(SubType<5, int, char, float, A>).name() << endl;
#endif
	return 0;
}