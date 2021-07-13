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
	using LinkA = MapLinker<MapDataA, size_t>;
	cout << typeid(LinkA).name() << endl;
	MapDataA a;
	LinkA::fillDebug(cout, a) << endl;
	LinkA::addDt(a, 1) = 10;
	LinkA::fillDebug(cout, a) << endl;
	size_t* pSize = LinkA::getDt(a, 1);
	if (pSize)
		cout << *pSize << endl;
	else
		cout << "NULL" << endl;
	
	MapDataB b;
	using LinkB = MapLinker<MapDataB, MapDataA, size_t>;
	cout << typeid(GetMapLinker<MapDataB>::Type).name() << endl;
	LinkB::addDt(b, 1, 2) = 20;
	LinkB::addDt(b, 1, 3) = 20;
	LinkB::fillDebug(cout, b) << endl;
	cout << MapLinker<MapDataB, MapDataA, size_t>::getDt(b, 1, 2) << endl;
	return 0;
}