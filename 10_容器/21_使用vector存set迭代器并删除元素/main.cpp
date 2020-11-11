#include "global.h"
#include "hTool.h"

using namespace std;
hTool::Container ctor(cout);

int main()
{
	set<int> s = { 1, 2, 3, 4, 5 };
	ctor(s);

	vector<set<int>::const_iterator> vIt;
	for (auto it = s.begin(); it != s.end(); ++it)
	{
		if (*it % 2 == 0)
			vIt.push_back(it);
	}

	for (auto& it : vIt)
		s.erase(it);
	ctor(s);

#if 0
	set<set<int>::const_iterator> sIt;
	for (auto it = s.begin(); it != s.end(); ++it)
	{
		if (*it % 3 == 0)
			sIt.insert(it);
	}

	for (auto& it : sIt)
		s.erase(it);
	ctor(s);
#endif

	return 0;
}