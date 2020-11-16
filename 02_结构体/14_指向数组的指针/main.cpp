#include <iostream>

using namespace std;

int main()
{
	size_t* pI = new size_t[4];
	for (size_t i = 0; i < 4; i++)
		cout << pI[i] << " ";
	cout << endl;

	memset(pI, 0, sizeof(size_t) * 4);
	for (size_t i = 0; i < 4; i++)
		cout << pI[i] << " ";
	cout << endl;

	for (size_t i = 0; i < 4; i++)
		pI[i] = i + 1;
	for (size_t i = 0; i < 4; i++)
		cout << pI[i] << " ";
	cout << endl;
	
	cout << ((size_t(*)[2])pI)[0][0] << " " << ((size_t(*)[2])pI)[0][1] << endl;
	cout << ((size_t(*)[2])pI)[1][0] << " " << ((size_t(*)[2])pI)[1][1] << endl;
	

	return 0;
}