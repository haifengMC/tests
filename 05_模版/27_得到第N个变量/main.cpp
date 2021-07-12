#include <ratio>
#include <typeinfo>
#include <type_traits>
#include <iostream>

using namespace std;

template <size_t N, typename...>
struct GetNType { using Type = void; };
template<typename _First, typename... _Rest>
struct GetNType<1, _First, _Rest...> { using Type = _First; };
template<size_t N, typename _FirstTy, typename... _Rest>
struct GetNType <N, _FirstTy, _Rest...> : public GetNType<std::ratio_subtract<std::ratio<N>, std::ratio<1>>::num, _Rest...> {};

template<size_t N>
struct GetNArg 
{
	template <typename... Args>
	using ArgTy = typename GetNType<N, Args...>::Type;

	template <typename Fst, typename... Args>
	static const ArgTy<Fst, Args...>& get(const Fst& t, const Args&... args)
	{
		return GetNArg<std::ratio_subtract<std::ratio<N>, std::ratio<1>>::num>::get(args...);
	}
	template <typename Fst, typename... Args>
	static ArgTy<Fst, Args...>& get(Fst& t, Args&... args)
	{
		return GetNArg<std::ratio_subtract<std::ratio<N>, std::ratio<1>>::num>::get(args...);
	}
};

template<>
struct GetNArg<1>
{
	template <typename Fst, typename... Args>
	static const Fst& get(const Fst& t, const Args&... args) { return t; }
	template <typename Fst, typename... Args>
	static Fst& get(Fst& t, Args&... args) { return t; }
};

int main()
{
	cout << GetNArg<1>::get(1, 1.5, "hello") << endl;
	cout << GetNArg<2>::get(1, 1.5, "hello") << endl;
	cout << GetNArg<3>::get(1, 1.5, "hello") << endl;

	int i = 10;
	double d = 1.1;
	const char* s = "hello";
	GetNArg<1>::get(i, d, s) = 20;
	GetNArg<2>::get(i, d, s) = 5.2;
	GetNArg<3>::get(i, d, s) = "world";
	cout << i << endl;
	cout << d << endl;
	cout << s << endl;

	return 0;
}