#include <iostream>

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

int main()
{
	E e = E::a;
	int i = (int)e;
	cout << i << endl;
	cout << e << endl;


	return 0;
}