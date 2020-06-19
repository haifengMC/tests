#include <iostream>

using namespace std;

template<typename T, size_t N, size_t M>
ostream& operator<<(ostream& os, const T(&arr)[N][M])
{
	for (const T(&a)[M] : arr)
	{
		for (const T& t : a)
			cout << t << " ";
		cout << "," << endl;
	}
	return os;
}

int main()
{
	int ai[][3] =
	{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9},
	};
	cout << ai << endl;
	float af[2][2] =
	{
		{1.0f, 0.5f},
		{0.3f, 0.2f}
	};
	cout << af << endl;
}