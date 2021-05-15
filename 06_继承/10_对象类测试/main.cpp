#include "global.h"
#include "hObjectBase.h"

using namespace std;

int main()
{
	{
		PhObj pObj = new hObjectBase(PWhObj());
		pObj->loadUi();
		//Debug(cout, pObj) << endl;
		//new hObjectBase(pObj);
		//PhObj pSubObj = new hObjectBase(pObj);
		//new hObjectBase(pObj);
		//new hObjectBase(pSubObj);
		Debug(cout, pObj) << endl;
		PhObj::debugMap(cout);
	}
	PhObj::debugMap(cout);

	return 0;
}
