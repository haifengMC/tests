#include <iostream>

using namespace std;

#define EXPAND(...) __VA_ARGS__

#define TO_STRING(X) TO_STRING1(X)
#define TO_STRING1(X) #X

#define COMB(X, Y) COMB1(X, Y)
#define COMB1(X, Y) X##Y

#define COMMA_M(X) ,X

#define DEC_1 0
#define DEC_2 1
#define DEC_3 2
#define DEC_4 3
#define DEC(n) COMB(DEC_, n)

#define RIS_1 2
#define RIS_2 3
#define RIS_3 4
#define RIS_4 5
#define RIS(n) COMB(RIS_, n)

#define _NUM(_0, _1, _2, _3, _4, N, ...) N
#define _NUM_ARGS() 4, 3, 2, 1, 0
#define _NUM_ARGS_CNT(...) EXPAND(_NUM(__VA_ARGS__))
#define NUM(...) EXPAND(_NUM_ARGS_CNT(0, ##__VA_ARGS__, _NUM_ARGS()))

#define REPEAT_1(f, n, X) f(n, X)
#define REPEAT_2(f, n, X, ...) COMB(f(n, X), COMMA(COMB(REPEAT_, EXPAND(NUM(##__VA_ARGS__)))(f, RIS(n), __VA_ARGS__)))
#define REPEAT_3(f, n, X, ...) COMB(f(n, X), COMMA(COMB(REPEAT_, EXPAND(NUM(##__VA_ARGS__)))(f, RIS(n), __VA_ARGS__)))
#define REPEAT_4(f, n, X, ...) COMB(f(n, X), COMMA(COMB(REPEAT_, EXPAND(NUM(##__VA_ARGS__)))(f, RIS(n), __VA_ARGS__)))
#define REPEAT(f, ...) EXPAND(COMB(REPEAT_, EXPAND(NUM(##__VA_ARGS__)))(f, 1, __VA_ARGS__))

#define TEST1(a, b) a - b

int main()
{
#define F1(n, X) X
#define F2(n, X) COMB(X, n)
	cout << TO_STRING(NUM(10, 20)) << endl;
	cout << TO_STRING(REPEAT(F1, 1, 2)) << endl;
	cout << TO_STRING(REPEAT(F1, 1, 2, 3)) << endl;
	cout << TO_STRING(REPEAT(F1, 1, 2, 3, 4)) << endl;
	cout << TO_STRING(REPEAT(F2, a, b)) << endl;
	cout << TO_STRING(REPEAT(F2, a, b, c)) << endl;
	cout << TO_STRING(REPEAT(F2, a, b, c, d)) << endl;
	cout << TO_STRING(NUM(3 - 1)) << endl;

	system("pause");
	return 0;
}