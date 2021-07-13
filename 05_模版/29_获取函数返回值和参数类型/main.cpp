#include <ratio>
#include <typeinfo>
#include <type_traits>
#include <iostream>

template <size_t N, typename...>
struct GetNType { using Type = void; };
template<typename First, typename... _Rest>
struct GetNType<1, First, _Rest...> { using Type = First; };
template<size_t N, typename FirstTy, typename... _Rest>
struct GetNType <N, FirstTy, _Rest...> : public GetNType<std::ratio_subtract<std::ratio<N>, std::ratio<1>>::num, _Rest...> {};

template <size_t, typename>
struct GetFuncRtParmTy { using Type = void; };
template<size_t N, typename RtTy, typename... Args>
struct GetFuncRtParmTy<N, RtTy(*)(Args...)> { using Type = typename GetNType<std::ratio_add<std::ratio<N>, std::ratio<1>>::num, RtTy, Args...>::Type; };

int f(char, double, std::ostream&) { return 0; }
int main()
{
	using namespace std;
	cout << typeid(GetFuncRtParmTy<0, decltype(&f)>::Type).name() << endl;
	cout << typeid(GetFuncRtParmTy<1, decltype(&f)>::Type).name() << endl;
	cout << typeid(GetFuncRtParmTy<2, decltype(&f)>::Type).name() << endl;
	cout << typeid(GetFuncRtParmTy<3, decltype(&f)>::Type).name() << endl;
	cout << typeid(GetFuncRtParmTy<4, decltype(&f)>::Type).name() << endl;
	return 0;
}

