#include <iostream>

using namespace std;

class A
{
public:
	A(int i)
	{
		if (i == 0)
		{
			cout << "a" << endl;
			return;
		}
		if (i == 1)
		{
			cout << "b" << endl;
			return;
		}

		cout << "none" << endl;
	}
};

int main()
{
	A a0(0), a1(1), a2(2);

	return 0;
}
