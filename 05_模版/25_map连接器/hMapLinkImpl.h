#pragma once

template<typename FirstTy, typename SecondTy, typename... Rest>
template <typename First, typename... Last>
MapLinker<FirstTy, SecondTy, Rest...>::SubType<sizeof...(Last)>& MapLinker<FirstTy, SecondTy, Rest...>::addDt(FirstTy& fstT, First fst, Last ... lasts)
{
	return MapLinker<SecondTy, Rest...>::addDt(fstT._mapDt[fst], lasts...);
}

template<typename FirstTy, typename SecondTy, typename... Rest>
template <typename First>
SecondTy& MapLinker<FirstTy, SecondTy, Rest...>::addDt(FirstTy& fstT, First fst) 
{ 
	return fstT._mapDt[fst];
}

template<typename FirstTy, typename SecondTy, typename... Rest>
template <typename First, typename... Last>
MapLinker<FirstTy, SecondTy, Rest...>::SubType<sizeof...(Last)>* MapLinker<FirstTy, SecondTy, Rest...>::getDt(FirstTy& fstT, First fst, Last ... lasts)
{
	auto it = fstT._mapDt.find(fst);
	if (it == fstT._mapDt.end())
		return NULL;

	return MapLinker<SecondTy, Rest...>::getDt(it->second, lasts...);
}

template<typename FirstTy, typename SecondTy, typename... Rest>
template <typename First>
SecondTy* MapLinker<FirstTy, SecondTy, Rest...>::getDt(FirstTy& fstT, First fst)
{ 
	auto it = fstT._mapDt.find(fst);
	if (it == fstT._mapDt.end())
		return NULL;

	return &it->second;
}

template<typename FirstTy, typename SecondTy, typename... Rest>
template <typename First, typename... Last>
const MapLinker<FirstTy, SecondTy, Rest...>::SubType<sizeof...(Last)>* MapLinker<FirstTy, SecondTy, Rest...>::getDt(const FirstTy& fstT, First fst, Last ... lasts)
{
	auto it = fstT._mapDt.find(fst);
	if (it == fstT._mapDt.end())
		return NULL;

	return MapLinker<SecondTy, Rest...>::getDt(it->second, lasts...);
}

template<typename FirstTy, typename SecondTy, typename... Rest>
template <typename First>
const SecondTy* MapLinker<FirstTy, SecondTy, Rest...>::getDt(const FirstTy& fstT, First fst)
{
	auto it = fstT._mapDt.find(fst);
	if (it == fstT._mapDt.end())
		return NULL;

	return &it->second;
}

template<typename FirstTy, typename SecondTy, typename... Rest>
template <typename First, typename... Last>
std::ostream& MapLinker<FirstTy, SecondTy, Rest...>::fillDebug(std::ostream& os, const FirstTy& fstT, First fst, Last ... lasts)
{
	os << "[" << fst << "]={";
	const SecondTy* pSec = getDt(fstT);
	do
	{
		if (!pSec)
			break;

		MapLinker<SecondTy, Rest...>::fillDebug(os, *pSec, lasts...);
	} while (0);

	return os << "}";
}

template<typename FirstTy, typename SecondTy, typename... Rest>
std::ostream& MapLinker<FirstTy, SecondTy, Rest...>::fillDebug(std::ostream& os, const FirstTy& fstT)
{
	os << "{";
	bool first = true;
	for (auto& pr : fstT._mapDt)
	{
		if (first) first = false;
		else os << ",";

		os << "[" << (size_t)pr.first << "]={";
		MapLinker<SecondTy, Rest...>::fillDebug(os, pr.second);
		os << "}";
	}

	return os << "}";
}

template<typename Ty>
std::ostream& MapLinker<Ty>::fillDebug(std::ostream& os, const Ty& t)
{
	if (hCallFuncBase<hMapFuncBase>::exec([](const hMapFuncBase& dt, std::ostream& os) { dt.fillDebug(os); }, t, os))
		return os;

	if (hCallFuncPutOut<std::ostream>::exec([](const Ty& dt, std::ostream& os) { os << dt; }, t, os))
		return os;

	return os << "Error";
}

