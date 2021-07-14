#pragma once

struct hMapFuncBase
{
	virtual ~hMapFuncBase() {}
	virtual std::ostream& fillOs(std::ostream& os) const { return os; }
};

struct _MapDataBase : hMapFuncBase {};
template<typename Key, typename Val>
struct MapDataBase : _MapDataBase
{
	using _MapData = std::map<Key, Val>;
	_MapData _mapDt;

	virtual ~MapDataBase() {}
};

template<typename...> class MapLinker {};

template<typename FirstTy, typename SecondTy, typename... Rest>
class MapLinker<FirstTy, SecondTy, Rest...>
{
public:
	template <size_t N>
	using SubType = typename GetNType<AddN<N>, SecondTy, Rest...>::Type;

	template <typename First, typename... Last>
	static SubType<sizeof...(Last)>* addDt(FirstTy* pFstT, First fst, Last ... lasts);
	template <typename First>
	static SecondTy* addDt(FirstTy* pFstT, First fst);

	template <typename First, typename... Last>
	static SubType<sizeof...(Last)>* getDt(FirstTy* pFstT, First fst, Last ... lasts);
	template <typename First>
	static SecondTy* getDt(FirstTy* pFstT, First fst);

	template <typename First, typename... Last>
	static const SubType<sizeof...(Last)>* getDt(const FirstTy* pFstT, First fst, Last ... lasts);
	template <typename First>
	static const SecondTy* getDt(const FirstTy* pFstT, First fst);
	template <typename First, typename... Last>
	static std::ostream& fillDebug(std::ostream& os, const FirstTy* pFstT, First fst, Last ... lasts);
	static std::ostream& fillDebug(std::ostream& os, const FirstTy* pFstT);
};

template<typename Ty>
class MapLinker<Ty>
{
public:
	static std::ostream& fillDebug(std::ostream& os, const Ty* pT);
};

namespace GetMapLinkerDetail
{
	template <typename Ty, bool isMapData>
	struct _GetNextLinkerTy { using Type = void; };
	template <typename Ty>
	struct _GetNextLinkerTy<Ty, true>
	{
		using Type = typename GetMapTy<typename Ty::_MapData>::Val;
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

template<typename Key, typename Val>
class MapData : public MapDataBase<Key, Val> 
{
	using Link = typename GetMapLinker<MapDataBase<Key, Val>>::Type;
public:
	template <typename... Args>
	auto addDt(Args ... args) { return Link::addDt(this, args...); }
	template <typename... Args>
	auto getDt(Args ... args) { return Link::getDt(this, args...); }
	template <typename... Args>
	auto getDt(Args ... args) const { return Link::getDt(this, args...); }
	template <typename... Args>
	std::ostream& fillDebug(std::ostream& os, Args ... args) const { return Link::fillDebug(os, this, args...); }
};
