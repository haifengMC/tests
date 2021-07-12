#pragma once

template <class...> struct PrintType {};
template<> struct PrintType<>
{
	static std::ostream& show(std::ostream& os) { return os; }
};
template<typename FirstTy, typename... _Rest>
struct PrintType <FirstTy, _Rest...>
{
	static std::ostream& show(std::ostream& os)
	{
		os << typeid(FirstTy).name() << " ";
		return PrintType<_Rest...>::show(os);
	}
};

template <class...> struct GetLastType { using Type = void; };
template<typename Last> struct GetLastType<Last>
{
	using Type = Last;
};
template<typename FirstTy, typename... _Rest>
struct GetLastType <FirstTy, _Rest...> : public GetLastType<_Rest...> {};

template <size_t N> struct DecSize
{
	static constexpr size_t Type = std::ratio_subtract<std::ratio<N>, std::ratio<1>>::num;
};

template <size_t N, size_t Add = 1>
constexpr size_t AddN = std::ratio_add<std::ratio<N>, std::ratio<Add>>::num;
template <size_t N>
constexpr size_t DecN = std::ratio_subtract<std::ratio<N>, std::ratio<1>>::num;
template <size_t N, class...> struct GetNType { using Type = void; };
template<typename First, typename... _Rest>
struct GetNType<1, First, _Rest...>
{
	using Type = First;
};
template<size_t N, typename FirstTy, typename... _Rest>
struct GetNType <N, FirstTy, _Rest...> : public GetNType<DecN<N>, _Rest...> {};
