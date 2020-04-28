#include <iostream>

using namespace std;

int main()
{
	int arr[2][3] =
	{
		{1, 2, 3},
		{4, 5, 6}
	};

	for (int *a : arr)
	{
		cout << a << " " << *a << endl;
	}

	int (*a)[3] = arr;
	cout << a << " " << **a << endl;
	++a;
	cout << a << " " << **a << endl;

	for (int (&a)[3] : arr)
	{
		for (int i : a)
		{
			cout << i << " ";
		}
		cout << endl;
	}

	for (const int(&a)[3] : arr)
	{
		for (int i : a)
		{
			i += 10;
			cout << i << " ";
		}
		cout << endl;
	}

	return 0;
}
