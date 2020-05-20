#include <iostream>

using namespace std;

#define EXPAND(...) __VA_ARGS__

#define TO_STRING(X) TO_STRING1(X)
#define TO_STRING1(X) #X

#define COMB(X, Y) COMB1(X, Y)
#define COMB1(X, Y) X##Y

#define SIGN__7 _1
#define SIGN__6 _1
#define SIGN__5 _1
#define SIGN__4 _1
#define SIGN__3 _1
#define SIGN__2 _1
#define SIGN__1 _1
#define SIGN_0 0
#define SIGN_1 1
#define SIGN_2 1
#define SIGN_3 1
#define SIGN_4 1
#define SIGN_5 1
#define SIGN_6 1
#define SIGN_7 1
#define SIGN(n) COMB(SIGN_, n)

#define OPP__7 7
#define OPP__6 6
#define OPP__5 5
#define OPP__4 4
#define OPP__3 3
#define OPP__2 2
#define OPP__1 1
#define OPP_0 0
#define OPP_1 _1
#define OPP_2 _2
#define OPP_3 _3
#define OPP_4 _4
#define OPP_5 _5
#define OPP_6 _6
#define OPP_7 _7
#define OPP(n) COMB(OPP_, n)

#define COMMA(X) ,X
#define SEM(X) ;X

#define DEC__7 _8
#define DEC__6 _7
#define DEC__5 _6
#define DEC__4 _5
#define DEC__3 _4
#define DEC__2 _3
#define DEC__1 _2
#define DEC_0 _1
#define DEC_1 0
#define DEC_2 1
#define DEC_3 2
#define DEC_4 3
#define DEC_5 4
#define DEC_6 5
#define DEC_7 6
#define DEC(n) COMB(DEC_, n)

#define RIS__7 _6
#define RIS__6 _5
#define RIS__5 _4
#define RIS__4 _3
#define RIS__3 _2
#define RIS__2 _1
#define RIS__1 0
#define RIS_0 1
#define RIS_1 2
#define RIS_2 3
#define RIS_3 4
#define RIS_4 5
#define RIS_5 6
#define RIS(n) COMB(RIS_, n)

//#define REPEAT_1(first, num, func, sort, X) func(first, X)
//#define REPEAT_2(first, num, func, sort, X) COMB(func(first, X), COMMA(COMB(REPEAT_, DEC(num))(sort(first), DEC(num), func, sort, X)))
//#define REPEAT_3(first, num, func, sort, X) COMB(func(first, X), COMMA(COMB(REPEAT_, DEC(num))(sort(first), DEC(num), func, sort, X)))

//#define REPEAT(n, f, X) COMB(REPEAT_, n)(1, n, f, RIS, X)

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
#define NOT_0 1
#define NOT_1 0
#define NOT(n) COMB(NOT_, n)
#define IF(n) SWITCH_CASE(RIS(SIGN(n)), 1, 0, 1)
#define NE(X, Y) SWITCH_CASE(RIS(SIGN(SUB(X, Y))), 1, 0, 1)
#define EQ(X, Y) SWITCH_CASE(RIS(SIGN(SUB(X, Y))), 0, 1, 0)
#define LS(X, Y) SWITCH_CASE(RIS(SIGN(SUB(X, Y))), 1, 0, 0)
#define LE(X, Y) SWITCH_CASE(RIS(SIGN(SUB(X, Y))), 1, 1, 0)
#define GT(X, Y) SWITCH_CASE(RIS(SIGN(SUB(X, Y))), 0, 0, 1)
#define GE(X, Y) SWITCH_CASE(RIS(SIGN(SUB(X, Y))), 0, 1, 1)

#define MIN(X, Y) SWITCH_CASE(LS(X, Y), Y, X)
#define MAX(X, Y) SWITCH_CASE(GT(X, Y), Y, X)

#define _NUM(_0, _1, _2, _3, _4, N, ...) N
#define _NUM_ARGS() 4, 3, 2, 1, 0
#define _NUM_ARGS_CNT(...) EXPAND(_NUM(__VA_ARGS__))
#define NUM(...) EXPAND(_NUM_ARGS_CNT(0, ##__VA_ARGS__, _NUM_ARGS()))

#define REPEAT_VA_1(first, num, total, func, sort, sep, X, ...) func(first, X)																			  
#define REPEAT_VA_2(first, num, total, func, sort, sep, X, ...) COMB(func(first, X), sep(COMB(REPEAT_VA_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, sort, sep, SWITCH_CASE(LE(num, 1),, X), ##__VA_ARGS__)))
#define REPEAT_VA_3(first, num, total, func, sort, sep, X, ...) COMB(func(first, X), sep(COMB(REPEAT_VA_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, sort, sep, SWITCH_CASE(LE(num, 1),, X), ##__VA_ARGS__)))
#define REPEAT_VA_4(first, num, total, func, sort, sep, X, ...) COMB(func(first, X), sep(COMB(REPEAT_VA_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, sort, sep, SWITCH_CASE(LE(num, 1),, X), ##__VA_ARGS__)))
#define REPEAT_VA(func, ...) EXPAND(COMB(REPEAT_VA_, EXPAND(NUM(##__VA_ARGS__)))(1, EXPAND(NUM(##__VA_ARGS__)), EXPAND(NUM(##__VA_ARGS__)), func, RIS, COMMA, __VA_ARGS__))
#define REPEAT_VA_SEP(func, sep, ...) EXPAND(COMB(REPEAT_VA_, EXPAND(NUM(##__VA_ARGS__)))(1, EXPAND(NUM(##__VA_ARGS__)), EXPAND(NUM(##__VA_ARGS__)), func, RIS, sep, __VA_ARGS__))
#define REPEAT(n, f, X) COMB(REPEAT_VA_, n)(1, 1, n, f, RIS, COMMA, X)
#define REPEAT_ZERO(n, f, X) COMB(f(0, X), COMMA(REPEAT(n, f, X)))
#define REVERSE_REPEAT(n, f, X) COMB(REPEAT_VA_, n)(n, 1, n, f, DEC, COMMA, X)
#define REVERSE_REPEAT_ZERO(n, f, X) COMB(REVERSE_REPEAT(n, f, X), COMMA(f(0, X)))

#define _ADDSUB_F(n, X) n															   
#define _SUB_CNT(...) EXPAND(GETARG(__VA_ARGS__))
#define _ADD_CNT(...) EXPAND(NUM(__VA_ARGS__))

//#define ADD(X, Y) _ADD_CNT(REPEAT(Y, _ADDSUB_F), REPEAT(X, _ADDSUB_F))
//#define ADD(X, Y) RIS(GETARG(Y, COMB(REPEAT_, Y)(X, Y, _ADDSUB_F, RIS, COMMA)))
#define ADD__7(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__6(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__5(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__4(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__3(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__2(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__1(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD_0(X, Y) Y
#define ADD_1(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_2(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_3(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_4(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_5(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_6(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_7(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD(X, Y) COMB(ADD_, X)(X, Y)
//#define SUB(X, Y) _SUB_CNT(RIS(RIS(X)), REPEAT_ZERO(Y, _ADDSUB_F), REPEAT_ZERO(X, _ADDSUB_F))
//#define SUB(X, Y) DEC(GETARG(Y, COMB(REPEAT_, Y)(X, Y, _ADDSUB_F, DEC, COMMA)))
#define SUB(X, Y) COMB(ADD_, X)(X, OPP(Y))

#define OR(X, Y) NOT(EQ(ADD(IF(X), IF(Y)), 0))
#define AD(X, Y) EQ(ADD(IF(X), IF(Y)), 2)

#define GET_SAFE_1(var, ret, n, X, ...) var[X]
#define GET_SAFE_2(var, ret, n, X, ...) var[X] ? EXPAND(COMB(GET_SAFE_, DEC(n))((*var[X]), ret, DEC(n), __VA_ARGS__)) : ret
#define GET_SAFE_3(var, ret, n, X, ...) var[X] ? EXPAND(COMB(GET_SAFE_, DEC(n))((*var[X]), ret, DEC(n), __VA_ARGS__)) : ret
#define GET_SAFE_RET(var, ret, ...) (EXPAND(COMB(GET_SAFE_, EXPAND(NUM(__VA_ARGS__)))(var, ret, EXPAND(NUM(__VA_ARGS__)), __VA_ARGS__)))
#define GET_SAFE(var, ...) GET_SAFE_RET(var, 0, __VA_ARGS__)


int main()
{
#define F(n, X) COMB(X, n)
	cout << TO_STRING(REPEAT_VA(F, a, b, c)) << endl;
	cout << TO_STRING(REPEAT_VA_SEP(F, SEM, a, b, c)) << endl;
	cout << TO_STRING(REPEAT(2, F, a)) << endl;
	cout << TO_STRING(REPEAT(3, F, a)) << endl;
	cout << TO_STRING(REPEAT(4, F, a)) << endl;
	cout << TO_STRING(REPEAT_ZERO(4, F, a)) << endl;
	cout << TO_STRING(REVERSE_REPEAT(4, F, a)) << endl;
	cout << TO_STRING(REVERSE_REPEAT_ZERO(4, F, a)) << endl;



	return 0;
}