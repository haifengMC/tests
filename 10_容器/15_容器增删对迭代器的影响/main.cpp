#include "global.h"
#include "hTool.h"

using namespace std;

hTool::Container ct(cout);

int main()
{
	{
		list<int> l = { 1, 2, 3 };
		list<int>::const_iterator it1 = find(l.begin(), l.end(), 3);
		l.push_back(4);
		list<int>::const_iterator it2 = find(l.begin(), l.end(), 3);

		cout << "it1 == it2:" <<
			(it1 == it2 ? "true" : "false") << endl;
		cout << "++it1 == ++it2:" <<
			(++it1 == ++it2 ? "true" : "false") << endl;
	}

	{
		vector<int> v = { 1, 2, 3 };
		vector<int>::const_iterator it1 = find(v.begin(), v.end(), 3);
		v.push_back(4);
		vector<int>::const_iterator it2 = find(v.begin(), v.end(), 3);

		cout << "it1 == it2:" <<
			(it1 == it2 ? "true" : "false") << endl;
		cout << "++it1 == ++it2:" <<
			(++it1 == ++it2 ? "true" : "false") << endl;
	}

	return 0;
}