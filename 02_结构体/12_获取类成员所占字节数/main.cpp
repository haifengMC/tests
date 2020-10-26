#include <iostream>

using namespace std;

class A
{
public:
	int i;
	char str[5];
};

int main()
{
	cout << sizeof(A::i) << endl;
	cout << sizeof(A::str) << endl;


	return 0;
}