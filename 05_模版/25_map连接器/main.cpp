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

template<typename _FirstTy, typename _SecondTy> 
class MapLinker<_FirstTy, _SecondTy>
{
public:
	/*
	template <class T, class ... Args>
	static _SecondTy* getDt(_FirstTy* pFst, T first, Args ... last)
	{
		if (!sizeof...(last))
			return NULL;

		if (!pFst)
			return NULL;

		return pFst->_getDt(first);
	}
	*/
};

template <size_t N, typename... _Ty>
using SubType = class GetNType<N, _Ty...>::Type;

template<typename _FirstTy, typename _SecondTy, typename... _Rest>
class MapLinker<_FirstTy, _SecondTy, _Rest...>
{
public:

	
	MapLinker() 
	{ 
		PrintType<_FirstTy, _SecondTy, _Rest...>::show(cout); 
		cout << endl;
	}
	/*
	template <class T, class ... Args>
	static SubType<sizeof...(Args)>* getDt(_FirstTy* pFst, T first, Args ... last)
	{
		if (!pFst)
			return NULL;

		_SecondTy* pSec = pFst->_getDt(first);
		if (!pSec)
			return NULL;

		return MapLinker<_SecondTy, _Rest...>::getDt(pSec, last...);
	}
	*/
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
	cout << typeid(SubType<0, int, char, float, MapDataA>).name() << endl;
	cout << typeid(SubType<1, int, char, float, MapDataA>).name() << endl;
	MapDataB b;
	MapLinker<MapDataB, MapDataA, size_t> link;
	//cout << typeid(MapLinker<MapDataB, MapDataA, size_t>).name() << endl;
	//MapDataA* pA = MapLinker<MapDataB, MapDataA, size_t>::getDt(&b, 1);;
	//MapDataA* pA = b.getDt(1);
	return 0;
}