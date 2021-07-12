#pragma once

template<typename FirstTy, typename SecondTy, typename... Rest>
template <typename First, typename... Last>
MapLinker<FirstTy, SecondTy, Rest...>::SubType<sizeof...(Last)>& MapLinker<FirstTy, SecondTy, Rest...>::addDt(FirstTy& fstT, First fst, Last ... lasts)
{
	return MapLinker<SecondTy, Rest...>::getDt(fstT._mapDt[fst], lasts...);
}

template<typename FirstTy, typename SecondTy, typename... Rest>
template <typename First>
static SecondTy& MapLinker<FirstTy, SecondTy, Rest...>::addDt(FirstTy& fstT, First fst) { return fstT._mapDt[fst]; }

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
static SecondTy* MapLinker<FirstTy, SecondTy, Rest...>::getDt(FirstTy& fstT, First fst)
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
static const SecondTy* MapLinker<FirstTy, SecondTy, Rest...>::getDt(const FirstTy& fstT, First fst)
{
	auto it = fstT._mapDt.find(fst);
	if (it == fstT._mapDt.end())
		return NULL;

	return &it->second;
}


