#include <iostream>

using namespace std;

template <typename T, typename U>
void f(int a, T* b, 
	typename common_type<T, U>::type c, 
	typename common_type<T, U>::type d) {}

int main()
{
	size_t i = 0;
	f(1, &i, 2, 3);


	return 0;
}