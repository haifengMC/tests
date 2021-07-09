#include <map>
#include <iostream>
#include <ratio>
#include <typeinfo>
#include <type_traits>

using namespace std;

template<typename Key, typename Val>
struct MapDataBase
{
	using MapData = std::map<Key, Val>;
	MapData _mapDt;

	Val* _getDt(Key k)
	{
		auto it = _mapDt.find(k);
		if (it != _mapDt.end())
			return &it->second;

		return NULL;
	}
};

template <class...> struct PrintType {};
template<> struct PrintType<>
{
	static std::ostream& show(std::ostream& os) { return os; }
};
template<typename _FirstTy, typename... _Rest>
struct PrintType <_FirstTy, _Rest...>
{
	static std::ostream& show(std::ostream& os)
	{
		os << typeid(_FirstTy).name() << " ";
		return PrintType<_Rest...>::show(os);
	}
};

template <class...> struct GetLastType { using Type = void; };
template<typename _Last> struct GetLastType<_Last>
{
	using Type = _Last;
};
template<typename _FirstTy, typename... _Rest>
struct GetLastType <_FirstTy, _Rest...> : public GetLastType<_Rest...> {};

template <size_t N> struct DecSize
{
	static constexpr size_t Type = std::ratio_subtract<std::ratio<N>, std::ratio<1>>::num;
};

template <size_t N>
constexpr size_t AddN = std::ratio_add<std::ratio<N>, std::ratio<1>>::num;
template <size_t N>
constexpr size_t DecN = std::ratio_subtract<std::ratio<N>, std::ratio<1>>::num;
template <size_t N, class...> struct GetNType { using Type = void; };
template<typename _First, typename... _Rest>
struct GetNType<1, _First, _Rest...>
{
	using Type = _First;
};
template<size_t N, typename _FirstTy, typename... _Rest>
struct GetNType <N, _FirstTy, _Rest...> : public GetNType<DecN<N>, _Rest...> {};

template<typename...> class MapLinker {};

template<typename _FirstTy, typename _SecondTy, typename... _Rest>
class MapLinker<_FirstTy, _SecondTy, _Rest...>
{
public:
	template <size_t N>
	using SubType = typename GetNType<N, _FirstTy, _SecondTy, _Rest...>::Type;

	template <typename ... Args>
	static SubType<sizeof...(Args)>* getDt(_FirstTy* pFst, T first, Args ... args)
	{
		switch (sizeof...(args))
		{
		case 0: return 
		default:
			break;
		}
		if (!pFst)
			return NULL;

		_SecondTy* pSec = pFst->_getDt(first);
		if (!pSec)
			return NULL;

		if (!sizeof...(last))
			return pSec;

		return MapLinker<_SecondTy, _Rest...>::getDt(pSec, last...);
	}
};

struct MapDataA : public MapDataBase<uint8_t, size_t>
{

};

struct MapDataB : public MapDataBase<uint8_t, MapDataA>
{
	//template <class T, class ... Args>
	//class GetNType<sizeof...(Args), MapDataA, size_t>::Type* getDt(T first, Args ... last) { return MapLinker<MapDataB, MapDataA, size_t>::getDt(this, first, last...); }
};

int main()
{
	//cout << typeid(MapDataA).name() << ":T" << endl;
	//cout << typeid(std::_Get_first_parameter<MapDataA::MapData>::type).name() << ":T" << endl;
	//PrintType<int, char, float, MapDataA>::show(cout);
	MapDataB b;
	//cout << typeid(MapLinker<MapDataB, MapDataA, size_t>).name() << endl;
	MapDataA* pA = MapLinker<MapDataB, MapDataA, size_t>::getDt(&b, 1);;
	//MapDataA* pA = b.getDt(1);
	return 0;
}