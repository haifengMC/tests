#include <iostream>

using namespace std;

#define EXPAND(...) __VA_ARGS__

#define TO_STRING(X) TO_STRING1(X)
#define TO_STRING1(X) #X


#define _NUM(_0, _1, _2, _3, N, ...) N
#define _NUM_ARGS() 3, 2, 1, 0
#define _NUM_ARGS_CNT(...) EXPAND(_NUM(__VA_ARGS__))
#define NUM(...) EXPAND(_NUM_ARGS_CNT(0, ##__VA_ARGS__, _NUM_ARGS()))

int main()
{
	cout << TO_STRING(NUM(10, 20)) << endl;

	return 0;
}