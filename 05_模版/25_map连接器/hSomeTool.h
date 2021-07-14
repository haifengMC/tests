#pragma once

template <typename Os, typename Ty, typename = void>
struct IsPutOut { static constexpr bool value = false; };

template <typename Os, typename Ty>
struct IsPutOut<Os, Ty, _STD void_t<decltype(_STD declval<Os>() << _STD declval<Ty>())>>
{
	static constexpr bool value = true;
};

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

template <typename Ty> struct GetMapTy;
template <typename _Key, typename _Val, typename _Pr, typename _Alloc>
struct GetMapTy<std::map<_Key, _Val, _Pr, _Alloc>>
{
	using Key = _Key;
	using Val = _Val;
	using Pr = _Pr;
	using Alloc = _Alloc;
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

template <size_t, typename> struct GetNTemplType;
template<template <typename, typename...> typename Ty, typename First, typename... Rest>
struct GetNTemplType<1, Ty<First, Rest...>> { using Type = First; };
template<size_t N, template <typename, typename...> typename Ty, typename First, typename... Rest>
struct GetNTemplType <N, Ty<First, Rest...>> : public GetNTemplType<std::ratio_subtract<std::ratio<N>, std::ratio<1>>::num, Ty<Rest...>> {};

namespace hCallFuncDetail
{
	template <bool>
	struct _hCallFuncBase
	{
		template <typename Func, typename Ty, typename... Args>
		static bool exec(Func, Ty&, Args&...) { return false; }
	};

	template <>
	struct _hCallFuncBase<true>
	{
		template <typename Func, typename Ty, typename... Args>
		static bool exec(Func f, Ty& t, Args&... args) 
		{
			f(t, args...); 
			return true;
		}
	};

	template <bool>
	struct _hCallFuncPutOut
	{
		template <typename Ty, typename... Args>
		static bool exec(Ty&, Args&...) { return false; }
	};

	template <>
	struct _hCallFuncPutOut<true>
	{
		template <typename Os, typename Ty>
		static bool exec(Os& os, Ty& t)
		{
			os << t;
			return true;
		}
	};
}

template <typename Base>
struct hCallFuncBase
{
	template <typename Func, typename Ty, typename... Args>
	static bool exec(Func f, Ty& t, Args&... args)
	{
		return hCallFuncDetail::_hCallFuncBase<std::is_base_of_v<Base, Ty>>::exec(f, t, args...);
	}
};

template <typename Os>
struct hCallFuncPutOut
{
	template <typename Ty>
	static bool exec(Os& os, Ty& t)
	{
		return hCallFuncDetail::_hCallFuncPutOut<IsPutOut<Os, Ty>::value>::exec(os, t);
	}
};

template <size_t, typename>
struct GetFuncRtParmTy { using Type = void; };
template<size_t N, typename RtTy, typename... Args>
struct GetFuncRtParmTy<N, RtTy(*)(Args...)> 
{ 
	using Type = typename GetNType<std::ratio_add<std::ratio<N>, std::ratio<1>>::num, RtTy, Args...>::Type; 
};
template<size_t N, typename Ty, typename RtTy, typename... Args>
struct GetFuncRtParmTy<N, RtTy(Ty::*)(Args...)> 
{
	using Type = typename GetNType < std::ratio_add < std::ratio<N>, std::ratio<1>>::num, RtTy, Args...>::Type;
};
