#include "global.h"
#include "hTool.h"

using namespace std;

hTool::Container ctor(cout);

int main()
{
	map<int, int> m;
	++m[0];
	++m[2];
	ctor(m);
	++m[2];
	++m[3];
	ctor(m);

	return 0;
}