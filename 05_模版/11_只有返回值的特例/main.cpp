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

//template<typename T1, typename T2>
//std::pair<T1, T2> func<pair<T1, T2>>()
//{
//	cout << "func 3" << endl;
//	return std::make_pair(T1(), T2());
//}

template<typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2 >& p)
{
	cout << "{" << p.first << "," << p.second << "}" << endl;
	return os;
}


int main()
{
	cout << func<int>() << endl;
	cout << func<char>() << endl;
	cout << func<pair<int, int>>() << endl;

	return 0;
}