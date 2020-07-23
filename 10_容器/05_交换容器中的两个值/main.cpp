#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <map>
#include <string>

using namespace std;



template<typename F, typename S>
ostream& operator<<(ostream& os, const pair<F, S>& p) 
{
	return os << "{" << p.first << ", " << p.second << "}";
}
class Container
{
	ostream& os;
public:
	Container(ostream& os) : os(os) {}

	template<typename T>
	ostream& operator() (const T& c)
	{
		bool first = true;
		os << "{";
		for (auto& t : c)
		{
			if (first) first = false;
			else os << ", ";

			os << t;
		}
		return os << "}";
	}
};


int main()
{
#if 0
	Container c(cout);

	vector<int> v = { 1, 2, 3 };
	c(v) << endl;
	list<int> l = { 4, 5, 6 };
	c(l) << endl;
	int a[] = { 7, 8, 9 };
	c(a) << endl;
	map<int, string> m = { {1, "peter"}, {2, "lucy"} };
	c(m) << endl;
#endif
	Container c(cout);

	vector<int> v = { 1, 2, 3, 4, 5, 6 };
	c(v) << endl;
	swap(v[2], v[4]);
	c(v) << endl;
	swap(v.front(), v.back());
	c(v) << endl;

	return 0;
}