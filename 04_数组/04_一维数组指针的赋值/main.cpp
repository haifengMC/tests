#include <iostream>

using namespace std;

int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6 };
	int(*parr)[2] = (int(*)[2])arr;
	cout << parr[0][0] << " " << parr[0][1] << endl;
	cout << parr[1][0] << " " << parr[1][1] << endl;
	cout << parr[2][0] << " " << parr[2][1] << endl;


	return 0;
}