#include <iostream>
#include <list>

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const list<T>& list)
{
	for (const T& t : list)
		os << t << " ";
	return os;
}

int main()
{
	list<int> l = { 1, 2, 3, 4, 5 };
	cout << l << endl;
	for (auto it = l.begin(); it != l.end();)
	{
		if (2 == *it || 4 == *it)
			it = l.erase(it);
		else
			++it;
	}
	cout << l << endl;
}