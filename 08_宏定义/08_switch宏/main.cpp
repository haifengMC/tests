#include <iostream>

using namespace std;

#define EXPAND(...) __VA_ARGS__

#define TO_STRING(X) TO_STRING1(X)
#define TO_STRING1(X) #X

#define COMB(X, Y) COMB1(X, Y)
#define COMB1(X, Y) X##Y

#define IF_0 0
#define IF_1 1
#define IF_2 1
#define IF_3 1
#define IF_4 1
#define IF_5 1
#define IF_6 1
#define IF_7 1
#define IF(n) COMB(IF_, n)
#define NOT_0 1
#define NOT_1 0
#define NO(n) COMB(NOT_, n)
#define EQ(X, Y) NOT(IF(SUB(X, Y)))

#define COMMA_M(X) ,X

#define DEC__1 _2
#define DEC_0 _1
#define DEC_1 0
#define DEC_2 1
#define DEC_3 2
#define DEC_4 3
#define DEC_5 4
#define DEC(n) COMB(DEC_, n)

#define RIS_0 1
#define RIS_1 2
#define RIS_2 3
#define RIS_3 4
#define RIS_4 5
#define RIS_5 6
#define RIS(n) COMB(RIS_, n)

#define REPEAT_1(first, num, func, sort, X) func(first, X)
#define REPEAT_2(first, num, func, sort, X) COMB(func(first, X), COMMA(COMB(REPEAT_, DEC(num))(sort(first), DEC(num), func, sort, X)))
#define REPEAT_3(first, num, func, sort, X) COMB(func(first, X), COMMA(COMB(REPEAT_, DEC(num))(sort(first), DEC(num), func, sort, X)))

#define REPEAT(n, f, X) COMB(REPEAT_, n)(1, n, f, RIS, X)
#define REPEAT_ZERO(n, f, X) COMB(0, COMMA(REPEAT(n, f, X)))
#define REVERSE_REPEAT(n, f, X) COMB(REPEAT_, n)(n, n, f, DEC, X)
#define REVERSE_REPEAT_ZERO(n, f, X) COMB(REVERSE_REPEAT(n, f, X), COMMA(0))

#define GETARG_1(n, func, X, ...) EXPAND(func(X, ##__VA_ARGS__))
#define GETARG_2(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_3(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_4(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_5(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))

#define GETARG_F(X) X
#define GETARG(N, ...) EXPAND(COMB(GETARG_, N)(N, GETARG_F, __VA_ARGS__))

#define CUTARGS_F(X, ...) __VA_ARGS__
#define CUTARGS(N, ...) EXPAND(COMB(GETARG_, N)(N, CUTARGS_F, __VA_ARGS__))

#define SWITCH_CASE(conf, ...) EXPAND(GETARG(RIS(conf), ##__VA_ARGS__))

#define _NUM(_0, _1, _2, _3, _4, N, ...) N
#define _NUM_ARGS() 4, 3, 2, 1, 0
#define _NUM_ARGS_CNT(...) EXPAND(_NUM(__VA_ARGS__))
#define NUM(...) EXPAND(_NUM_ARGS_CNT(0, ##__VA_ARGS__, _NUM_ARGS()))

#define REPEAT_VA_1(first, num, func, sort, X) func(first, X)
#define REPEAT_VA_2(first, num, func, sort, X, ...) COMB(func(first, X), COMMA(COMB(REPEAT_VA_, DEC(num))(sort(first), DEC(num), func, sort, __VA_ARGS__)))
#define REPEAT_VA_3(first, num, func, sort, X, ...) COMB(func(first, X), COMMA(COMB(REPEAT_VA_, DEC(num))(sort(first), DEC(num), func, sort, __VA_ARGS__)))
#define REPEAT_VA_4(first, num, func, sort, X, ...) COMB(func(first, X), COMMA(COMB(REPEAT_VA_, DEC(num))(sort(first), DEC(num), func, sort, __VA_ARGS__)))
#define REPEAT_VA(func, ...) EXPAND(COMB(REPEAT_VA_, EXPAND(NUM(##__VA_ARGS__)))(1, EXPAND(NUM(##__VA_ARGS__)), func, RIS, __VA_ARGS__))\

#define _ADDSUB_F(n, X) n															   
#define _SUB_CNT(...) EXPAND(GETARG(__VA_ARGS__))
#define _ADD_CNT(...) EXPAND(NUM(__VA_ARGS__))
//#define SUB(X, Y) _SUB_CNT(RIS(RIS(X)), REPEAT_ZERO(Y, _ADDSUB_F), REPEAT_ZERO(X, _ADDSUB_F))
#define SUB(X, Y) DEC(GETARG(Y, COMB(REPEAT_, Y)(X, Y, _ADDSUB_F, DEC, COMMA)))
#define ADD(X, Y) _ADD_CNT(REPEAT(Y, _ADDSUB_F), REPEAT(X, _ADDSUB_F))

int main()
{
	cout << TO_STRING(EQ(2, 3)) << endl;
	cout << TO_STRING(EQ(2, 2)) << endl;

#define cA a
#define B b
#define C c
	cout << TO_STRING(SWITCH_CASE(0, cA, B, C)) << endl;
	cout << TO_STRING(SWITCH_CASE(1, cA, B, C)) << endl;
	cout << TO_STRING(SWITCH_CASE(2, cA, B, C)) << endl;

	cout << TO_STRING(SUB(2, 1)) << endl;
	cout << TO_STRING(SUB(1, -1)) << endl;


	return 0;
}