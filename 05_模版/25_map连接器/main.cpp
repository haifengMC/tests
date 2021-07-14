#include <map>
#include <iostream>
#include <ratio>
#include <typeinfo>
#include <type_traits>

#include "hSomeTool.h"
#include "hMapLink.h"
#include "hMapLinkImpl.h"

using namespace std;

struct OtherData 
{
	std::ostream& fillOs(std::ostream& os) const { return os << "OtherData"; }
};

struct MapDataA : public MapData<uint8_t, size_t>
{
	std::ostream& fillOs(std::ostream& os) const { return os << "MapDataA"; }
};

struct MapDataB : public MapData<uint8_t, MapDataA>
{
	std::ostream& fillOs(std::ostream& os) const { return os << "MapDataB"; }
};

int main()
{
	MapDataB b;
	b.fillDebug(cout) << endl;
	*b.addDt(1, 2) = 30;
	*b.addDt(1, 3) = 40;
	*b.addDt(2, 1) = 50;
	b.fillDebug(cout) << endl;
	MapDataA* pA = b.getDt(2);
	*pA->addDt(3) = 300;
	*pA->addDt(4) = 400;
	*pA->addDt(5) = 500;
	pA->fillDebug(cout) << endl;
	b.fillDebug(cout, 1) << endl;
	b.fillDebug(cout) << endl;

	return 0;
}