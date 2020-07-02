#include <iostream>

using namespace std;

template<typename T>
T func()
{
	cout << "func 1" << endl;
	return T();
}

template<>
char func<char>()
{
	cout << "func 2" << endl;
	return 'h';
}


int main()
{
	cout << func<int>() << endl;
	cout << func<char>() << endl;

	return 0;
}