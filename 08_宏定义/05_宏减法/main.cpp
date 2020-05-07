#include <iostream>

using namespace std;

#define EXPAND(...) __VA_ARGS__

#define TO_STRING(X) TO_STRING1(X)
#define TO_STRING1(X) #X

#define COMB(X, Y) COMB1(X, Y)
#define COMB1(X, Y) X##Y

#define COMMA(X) ,X

#define DEC_1 0
#define DEC_2 1
#define DEC_3 2
#define DEC_4 3
#define DEC_5 4
#define DEC(n) COMB(DEC_, n)

#define RIS_1 2
#define RIS_2 3
#define RIS_3 4
#define RIS_4 5
#define RIS_5 6
#define RIS(n) COMB(RIS_, n)

#define _NUM(_0, _1, _2, _3, _4, N, ...) N
#define _NUM_ARGS() 4, 3, 2, 1, 0
#define _NUM_ARGS_CNT(...) EXPAND(_NUM(__VA_ARGS__))
#define NUM(...) EXPAND(_NUM_ARGS_CNT(0, ##__VA_ARGS__, _NUM_ARGS()))


#define REPEAT_0(n, f, e) f(n, e)
#define REPEAT_1(n, f, e) COMB(COMB(REPEAT_, DEC(n))(DEC(n), f, e), COMMA(f(n, e)))
#define REPEAT_2(n, f, e) COMB(COMB(REPEAT_, DEC(n))(DEC(n), f, e), COMMA(f(n, e)))
#define REPEAT_3(n, f, e) COMB(COMB(REPEAT_, DEC(n))(DEC(n), f, e), COMMA(f(n, e)))
#define REPEAT(n, f, e) COMB(REPEAT_, n)(n, f, e)

#define REPEAT_VA_1(f, n, X) f(n, X)
#define REPEAT_VA_2(f, n, X, ...) COMB(f(n, X), COMMA(COMB(REPEAT_VA_, EXPAND(NUM(##__VA_ARGS__)))(f, RIS(n), __VA_ARGS__)))
#define REPEAT_VA_3(f, n, X, ...) COMB(f(n, X), COMMA(COMB(REPEAT_VA_, EXPAND(NUM(##__VA_ARGS__)))(f, RIS(n), __VA_ARGS__)))
#define REPEAT_VA_4(f, n, X, ...) COMB(f(n, X), COMMA(COMB(REPEAT_VA_, EXPAND(NUM(##__VA_ARGS__)))(f, RIS(n), __VA_ARGS__)))
#define REPEAT_VA(f, ...) EXPAND(COMB(REPEAT_VA_, EXPAND(NUM(##__VA_ARGS__)))(f, 1, __VA_ARGS__))

#define GETARG_1(n, X) X
#define GETARG_2(n, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), __VA_ARGS__))
#define GETARG_3(n, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), __VA_ARGS__))
#define GETARG_4(n, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), __VA_ARGS__))
#define GETARG_5(n, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), __VA_ARGS__))
#define GETARG(N, ...) EXPAND(COMB(GETARG_, N)(N, __VA_ARGS__))

#define _SUB_F(n, X) n
#define _SUB_CNT(...) EXPAND(GETARG(__VA_ARGS__))
#define SUB(X, Y) _SUB_CNT(RIS(RIS(X)), REPEAT(Y, _SUB_F), REPEAT(X, _SUB_F))

int main()
{
#define F(n, X) n
	cout << TO_STRING(REPEAT_VA(F, a, b)) << endl;
	cout << TO_STRING(REPEAT(2, _SUB_F)) << endl;
	cout << TO_STRING(GETARG(4, 0, 1, 0, 1, 2)) << endl;
	cout << TO_STRING(SUB(2, 1)) << endl;
	cout << TO_STRING(SUB(3, 1)) << endl;

	system("pause");
	return 0;
}