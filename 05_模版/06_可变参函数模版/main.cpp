#include <iostream>

using namespace std;

void debug()
{
	cout << "empty" << endl;
}

template <class T, class ... Args>
void debug(T first, Args ... last)
{
	cout << "parameter " << first << endl;
	debug(last...);
}

int main()
{
	debug(1, 2, 3);

	return 0;
}