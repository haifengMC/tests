#include <iostream>

using namespace std;

#define PI 3.14
#define MUL_PI(n) n * PI
#define TWO 2

//对宏参数进行了#或者##,那么该宏参数不会被展开，为了让x充分展开写TO_STRING1
#define TO_STRING(x) TO_STRING1(x)
#define TO_STRING1(x) #x

int main()
{
	cout << MUL_PI(TWO) << endl;
	cout << TO_STRING(hello) << endl;

	return 0;
}