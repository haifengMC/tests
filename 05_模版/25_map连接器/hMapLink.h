#pragma once

struct hMapFuncBase
{
	virtual ~hMapFuncBase() {}
	virtual std::ostream& fillDebug(std::ostream& os) const { return os; }
};

struct _MapDataBase : hMapFuncBase {};
template<typename Key, typename Val>
struct MapDataBase : _MapDataBase
{
	using MapData = std::map<Key, Val>;
	MapData _mapDt;
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
	template <typename First, typename... Last>
	static std::ostream& fillDebug(std::ostream& os, const FirstTy& fstT, First fst, Last ... lasts);
	static std::ostream& fillDebug(std::ostream& os, const FirstTy& fstT);
};

template<typename Ty>
class MapLinker<Ty>
{
public:
	static std::ostream& fillDebug(std::ostream& os, const Ty& t);
};

namespace GetMapLinkerDetail
{
	template <typename Ty, bool isMapData>
	struct _GetNextLinkerTy { using Type = void; };
	template <typename Ty>
	struct _GetNextLinkerTy<Ty, true>
	{
		using Type = typename GetMapTy<typename Ty::MapData>::Val;
	};

	template <bool isMapData, typename, typename... Rest>
	struct _GetMapLinker { using Type = MapLinker<Rest...>; };

	template <typename First, typename... Rest>
	struct _GetMapLinker<true, First, Rest...>
	{
		using Type = typename _GetMapLinker<std::is_base_of_v<_MapDataBase, First>, typename _GetNextLinkerTy<First, std::is_base_of_v<_MapDataBase, First>>::Type, Rest..., First>::Type;
	};
}

template<typename Ty>
struct GetMapLinker { using Type = typename GetMapLinkerDetail::_GetMapLinker<std::is_base_of_v<_MapDataBase, Ty>, Ty>::Type; };


