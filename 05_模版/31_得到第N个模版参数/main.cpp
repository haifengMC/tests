#include <map>
#include <iostream>
#include <ratio>
#include <typeinfo>
#include <type_traits>


template <size_t, typename> struct GetNTemplType;
template<template <typename, typename...> typename Ty, typename First, typename... Rest>
struct GetNTemplType<1, Ty<First, Rest...>> { using Type = First; };
template<size_t N, template <typename, typename...> typename Ty, typename First, typename... Rest>
struct GetNTemplType <N, Ty<First, Rest...>> : public GetNTemplType<std::ratio_subtract<std::ratio<N>, std::ratio<1>>::num, Ty<Rest...>> {};

template <typename, size_t = 1> class A {};
template <typename, typename> class B {};
class C {};

int main()
{
	using namespace std;
	cout << typeid(GetNTemplType<1, B<int, double>>::Type).name() << endl;
	//cout << typeid(GetNTemplType<2, A<int>>::Type).name() << endl;
	cout << typeid(GetNTemplType<3, std::map<int, double>>::Type).name() << endl;
	cout << typeid(GetNTemplType<4, std::map<int, double>>::Type).name() << endl;
	cout << typeid(GetNTemplType<5, std::map<int, double>>::Type).name() << endl;
	cout << typeid(GetNTemplType<6, std::map<int, double>>::Type).name() << endl;
	cout << typeid(GetNTemplType<7, std::map<int, double>>::Type).name() << endl;
	return 0;
}