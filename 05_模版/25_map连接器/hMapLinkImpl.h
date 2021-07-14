#pragma once

template<typename FirstTy, typename SecondTy, typename... Rest>
template <typename First, typename... Last>
MapLinker<FirstTy, SecondTy, Rest...>::SubType<sizeof...(Last)>* MapLinker<FirstTy, SecondTy, Rest...>::addDt(FirstTy* pFstT, First fst, Last ... lasts)
{
	if (!pFstT)
		return NULL;

	return MapLinker<SecondTy, Rest...>::addDt(&pFstT->_mapDt[fst], lasts...);
}

template<typename FirstTy, typename SecondTy, typename... Rest>
template <typename First>
SecondTy* MapLinker<FirstTy, SecondTy, Rest...>::addDt(FirstTy* pFstT, First fst)
{
	if (!pFstT)
		return NULL;

	return &pFstT->_mapDt[fst];
}

template<typename FirstTy, typename SecondTy, typename... Rest>
template <typename First, typename... Last>
MapLinker<FirstTy, SecondTy, Rest...>::SubType<sizeof...(Last)>* MapLinker<FirstTy, SecondTy, Rest...>::getDt(FirstTy* pFstT, First fst, Last ... lasts)
{
	if (!pFstT)
		return NULL;

	auto it = pFstT->_mapDt.find(fst);
	if (it == pFstT->_mapDt.end())
		return NULL;

	return MapLinker<SecondTy, Rest...>::getDt(it->second, lasts...);
}

template<typename FirstTy, typename SecondTy, typename... Rest>
template <typename First>
SecondTy* MapLinker<FirstTy, SecondTy, Rest...>::getDt(FirstTy* pFstT, First fst)
{
	if (!pFstT)
		return NULL;

	auto it = pFstT->_mapDt.find(fst);
	if (it == pFstT->_mapDt.end())
		return NULL;

	return &it->second;
}

template<typename FirstTy, typename SecondTy, typename... Rest>
template <typename First, typename... Last>
const MapLinker<FirstTy, SecondTy, Rest...>::SubType<sizeof...(Last)>* MapLinker<FirstTy, SecondTy, Rest...>::getDt(const FirstTy* pFstT, First fst, Last ... lasts)
{
	if (!pFstT)
		return NULL;

	auto it = pFstT->_mapDt.find(fst);
	if (it == pFstT->_mapDt.end())
		return NULL;

	return MapLinker<SecondTy, Rest...>::getDt(it->second, lasts...);
}

template<typename FirstTy, typename SecondTy, typename... Rest>
template <typename First>
const SecondTy* MapLinker<FirstTy, SecondTy, Rest...>::getDt(const FirstTy* pFstT, First fst)
{
	if (!pFstT)
		return NULL;

	auto it = pFstT->_mapDt.find(fst);
	if (it == pFstT->_mapDt.end())
		return NULL;

	return &it->second;
}

template<typename FirstTy, typename SecondTy, typename... Rest>
template <typename First, typename... Last>
std::ostream& MapLinker<FirstTy, SecondTy, Rest...>::fillDebug(std::ostream& os, const FirstTy* pFstT, First fst, Last ... lasts)
{
	if (!pFstT)
		return os;

	os << "[" << fst << "]={";
	const SecondTy* pSec = getDt(pFstT, fst);
	do
	{
		if (!pSec)
			break;

		MapLinker<SecondTy, Rest...>::fillDebug(os, pSec, lasts...);
	} while (0);

	return os << "}";
}

template<typename FirstTy, typename SecondTy, typename... Rest>
std::ostream& MapLinker<FirstTy, SecondTy, Rest...>::fillDebug(std::ostream& os, const FirstTy* pFstT)
{
	if (!pFstT)
		return os;

	hCallFuncBase<hMapFuncBase>::exec([](const hMapFuncBase& dt, std::ostream& os) { dt.fillOs(os); }, *pFstT, os);

	os << "{";
	bool first = true;
	for (auto& pr : pFstT->_mapDt)
	{
		if (first) first = false;
		else os << ",";

		os << "[" << (size_t)pr.first << "]={";
		MapLinker<SecondTy, Rest...>::fillDebug(os, &pr.second);
		os << "}";
	}

	return os << "}";
}

template<typename Ty>
std::ostream& MapLinker<Ty>::fillDebug(std::ostream& os, const Ty* pT)
{
	if (!pT)
		return os;

	if (hCallFuncBase<hMapFuncBase>::exec([](const hMapFuncBase& dt, std::ostream& os) { dt.fillOs(os); }, *pT, os))
		return os;

	if (hCallFuncPutOut<std::ostream>::exec(os, *pT))
		return os;

	return os << "Error";
}

