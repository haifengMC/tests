#include <iostream>
#include <map>

using namespace std;

int main()
{
	map<int, int> m;
	auto itPair = m.insert(make_pair(1, 2));
	auto it1 = itPair.first;
	cout << it1->second++ << endl;
	map<int, int>::iterator it2 = itPair.first;
	cout << it2->second << endl;

	return 0;
}