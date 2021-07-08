#include <map>
#include <iostream>
#include <typeinfo>
#include <type_traits>

using namespace std;

template<typename Key, typename Val>
struct MapDataBase
{
	using MapData = std::map<Key, Val>;
	MapData _mapDt;

	Val* getDt(Key k)
	{
		auto it = _mapDt.find(k);
		if (it != _mapDt.end())
			return &it->second;

		return NULL;
	}
};

struct MapDataA : public MapDataBase<uint8_t, size_t>
{

};

struct MapDataB : public MapDataBase<uint8_t, MapDataA>
{

};
/*
template<typename...> class MapLinker {};

template<typename RootMap>
class MapLinker
{
public:

};

template<typename Head, typename... Tail>  // 递归的偏特化定义
class MapLinker<Head, Tail...> : public MapLinker<Tail...>
{
	MapLinker()
};
*/

template <class...> struct PrintType {};
template<> struct PrintType<>
{
	static std::ostream& show(std::ostream& os) { return os; }
};
template<typename _First, typename... _Rest>
struct PrintType <_First, _Rest...>
{
	static std::ostream& show(std::ostream& os)
	{
		os << typeid(_First).name() << " ";
		return PrintType<_Rest...>::show(os);
	}
};

int main()
{
	cout << typeid(MapDataA).name() << ":T" << endl;
	cout << typeid(std::_Get_first_parameter<MapDataA::MapData>::type).name() << ":T" << endl;
	PrintType<int, char, float, MapDataA>::show(cout);
	return 0;
}