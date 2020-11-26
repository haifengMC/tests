#include <iostream>
#include <map>
#include <string>

using namespace std;

#define ENUM_BEG(E)\
	enum class E : size_t

#define ENUM_END(E) ;\
	ostream& operator<<(ostream&os, const E& e)\
	{\
		return os << (size_t)e;\
	}


ENUM_BEG(E)
{
	a = 10,
	b,
}
ENUM_END(E)

enum 
{
	//A = "a",
};

int main()
{
	E e = E::a;
	E e2 = E::b;
	int i = (int)e;
	cout << i << endl;
	cout << e << endl;
	cout << (e < e2) << endl;
	map<E, string> m;
	m[e] = "e";
	m[e2] = "e2";
	for (pair<E, const string>p : m)
	{
		cout << p.first << " " << p.second << endl;
	}

	return 0;
}