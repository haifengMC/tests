#include <iostream>

using namespace std;

enum class E : size_t
{
	a = 10,
	b,
};

int main()
{
	E e = E::a;
	int i = (int)e;
	cout << i << endl;
	//cout << e << endl;


	return 0;
}