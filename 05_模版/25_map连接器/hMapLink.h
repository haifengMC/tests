#pragma once

template<typename Key, typename Val>
struct MapDataBase
{
	using MapData = std::map<Key, Val>;
	MapData _mapDt;

	virtual std::ostream& fillDebug(std::ostream&) {}
};

template<typename...> class MapLinker {};

template<typename FirstTy, typename SecondTy, typename... Rest>
class MapLinker<FirstTy, SecondTy, Rest...>
{
public:
	template <size_t N>
	using SubType = typename GetNType<AddN<N>, SecondTy, Rest...>::Type;

	template <typename First, typename... Last>
	static SubType<sizeof...(Last)>& addDt(FirstTy& fstT, First fst, Last ... lasts);
	template <typename First>
	static SecondTy& addDt(FirstTy& fstT, First fst);

	template <typename First, typename... Last>
	static SubType<sizeof...(Last)>* getDt(FirstTy& fstT, First fst, Last ... lasts);
	template <typename First>
	static SecondTy* getDt(FirstTy& fstT, First fst);

	template <typename First, typename... Last>
	static const SubType<sizeof...(Last)>* getDt(const FirstTy& fstT, First fst, Last ... lasts);
	template <typename First>
	static const SecondTy* getDt(const FirstTy& fstT, First fst);


};

