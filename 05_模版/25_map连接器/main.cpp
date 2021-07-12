#include <map>
#include <iostream>
#include <ratio>
#include <typeinfo>
#include <type_traits>

#include "hSomeTool.h"
#include "hMapLink.h"
#include "hMapLinkImpl.h"

using namespace std;

struct MapDataA : public MapDataBase<uint8_t, size_t>
{

};

struct MapDataB : public MapDataBase<uint8_t, MapDataA>
{
};

int main()
{
	//cout << typeid(MapDataA).name() << ":T" << endl;
	//cout << typeid(std::_Get_first_parameter<MapDataA::MapData>::type).name() << ":T" << endl;
	//PrintType<int, char, float, MapDataA>::show(cout);

	//cout << typeid(MapLinker<MapDataB, MapDataA, size_t>).name() << endl;
	MapDataA a;
	using LinkA = MapLinker<MapDataA, size_t>;
	LinkA::addDt(a, 1) = 10;
	size_t* pSize = LinkA::getDt(a, 1);
	if (pSize)
		cout << *pSize << endl;
	else
		cout << "NULL" << endl;

	MapDataB b;
	MapDataA* pA = MapLinker<MapDataB, MapDataA, size_t>::getDt(b, 1);
	return 0;
}