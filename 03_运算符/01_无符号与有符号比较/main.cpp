#include <iostream>

using namespace std;

int main()
{
	unsigned int u1 = 0;
	int i1 = -1;
	if (u1 > -1)
	{
		cout << 1 << endl;
	}

	if (u1 > i1)
	{
		cout << 2 << endl;
	}

	if (-1 < u1)
	{
		cout << 3 << endl;
	}

	if (i1 < u1)
	{
		cout << 4 << endl;
	}

	if ((int)u1 > -1)
	{
		cout << 5 << endl;
	}

	if ((int)u1 > i1)
	{
		cout << 6 << endl;
	}

	unsigned int u2 = 2;
	int i2 = -1;
	if (u2 > -i2)
	{
		cout << 7 << endl;
	}

	unsigned int u3 = 2;
	int i3 = -4;
	if (u3 + i3 > 0)
	{
		cout << 8 << endl;
	}

	if (i3 + u3 > 0)
	{
		cout << 9 << endl;
	}



	return 0;
}