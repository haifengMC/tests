#include "global.h"
#include "hObjectBase.h"

using namespace std;

int main()
{
	{
		PhObj pObj = new hObjectBase(PWhObj());
		Debug(cout, pObj) << endl;
		new hObjectBase(pObj.dynamic());
		PhObj pSubObj = new hObjectBase(pObj.dynamic());
		new hObjectBase(pObj.dynamic());
		new hObjectBase(pSubObj.dynamic());
		Debug(cout, pObj) << endl;
		PhObj::debugMap(cout);
	}
	PhObj::debugMap(cout);

	return 0;
}
