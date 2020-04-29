#include <iostream>

using namespace std;

int main()
{
	int arr[3] = { 1, 2, 3 };

	for (const int& a : arr)
	{
		cout << a << endl;
	}

	{
		int i = 0;
		for (const int& a : { 11, 12, 13 })
		{
			arr[i++] = a;
		}
	}

	for (const int& a : arr)
	{
		cout << a << endl;
	}

	int arr2[3][2] =
	{
		{ 1, 2 },
		{ 3, 4 },
		{ 5, 6 },
	};

	for (const int (&arr)[2] : arr2)
	{
		for (const int& a : arr)
			cout << a << " ";
		cout << endl;
	}

	{
		int* i = (int*)arr2;
		for (const int& a : { 11, 12, 13, 14, 15, 16 })
		{
			*(i++) = a;
		}
	}

	for (const int(&arr)[2] : arr2)
	{
		for (const int& a : arr)
			cout << a << " ";
		cout << endl;
	}



	return 0;
}