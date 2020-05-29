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
#define ABS(n) SWITCH_CASE(EQ(SIGN(n), _1), n, OPP(n))

#define COMMA_M(X) ,X
#define SEM_M(X) ;X
#define EXCP_M(X) !X
#define OR_M(X) ||X

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

#define CUTARGS_B_1(n, X, ...) X
#define CUTARGS_B_2(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_3(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_4(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_5(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B(N, ...) EXPAND(COMB(CUTARGS_B_, N)(N, ##__VA_ARGS__))

#define SWITCH_CASE(conf, ...) EXPAND(GETARG(RIS(conf), ##__VA_ARGS__))
#define SWITCH_CASE_ARGS_N(conf, n, ...) EXPAND(COMB(GETARG_, RIS(conf))(RIS(conf), GETARG_F, CUTARGS_B, CUTARGS)(n, ##__VA_ARGS__))
#define SWITCH_CASE_ARGS(conf, ...) EXPAND(SWITCH_CASE_ARGS_N(conf, 1, ##__VA_ARGS__))
#define NO_0 1
#define NO_1 0
#define NO(n) COMB(NO_, n)
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

#define REPEAT_FUNC(func, ...) EXPAND(func(__VA_ARGS__))
#define REPEAT_1(first, num, total, func, funcN, sort, sep, ...) REPEAT_FUNC(func, first, EXPAND(CUTARGS_B(funcN, ##__VA_ARGS__)))																			  
#define REPEAT_2(first, num, total, func, funcN, sort, sep, ...) COMB(REPEAT_FUNC(func, first, CUTARGS_B(funcN, ##__VA_ARGS__)), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN,sort, sep, SWITCH_CASE_ARGS_N(GT(num, 1), funcN, ##__VA_ARGS__))))
#define REPEAT_3(first, num, total, func, funcN, sort, sep, ...) COMB(REPEAT_FUNC(func, first, CUTARGS_B(funcN, ##__VA_ARGS__)), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN,sort, sep, SWITCH_CASE_ARGS_N(GT(num, 1), funcN, ##__VA_ARGS__))))
#define REPEAT_4(first, num, total, func, funcN, sort, sep, ...) COMB(REPEAT_FUNC(func, first, CUTARGS_B(funcN, ##__VA_ARGS__)), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN,sort, sep, SWITCH_CASE_ARGS_N(GT(num, 1), funcN, ##__VA_ARGS__))))

#define REPEAT_N_F_SEP(n, f, fn, sep, ...) COMB(REPEAT_, n)(1, DIV(EXPAND(NUM(##__VA_ARGS__)), fn), n, f, fn, RIS, sep, ##__VA_ARGS__)
#define REPEAT_N_F_SEP_ZERO(n, f, fn, sep, ...) COMB(f(0, CUTARGS_B(fn, ##__VA_ARGS__)), COMMA_M(REPEAT_N_F_SEP(n, f, fn, sep, CUTARGS(1, ##__VA_ARGS__))))
#define REVERSE_REPEAT_N_F_SEP(n, f, fn, sep, ...) COMB(REPEAT_, n)(n, DIV(EXPAND(NUM(##__VA_ARGS__)), fn), n, f, fn, DEC, sep, ##__VA_ARGS__)
#define REVERSE_REPEAT_N_F_SEP_ZERO(n, f, fn, sep, ...) COMB(REVERSE_REPEAT_N_F_SEP(n, f, fn, sep, ##__VA_ARGS__), COMMA_M(f(0, SWITCH_CASE(LS(n, EXPAND(NUM(##__VA_ARGS__))), GETARG(EXPAND(NUM(##__VA_ARGS__)), ##__VA_ARGS__), GETARG(n, ##__VA_ARGS__)))))

#define REPEAT_N_F(n, f, fn, ...) EXPAND(REPEAT_N_F_SEP(n, f, fn, COMMA_M, ##__VA_ARGS__))
#define REPEAT_N_F_ZERO(n, f, fn, ...) EXPAND(REPEAT_N_F_SEP_ZERO(n, f, fn, COMMA_M, ##__VA_ARGS__))
#define REVERSE_REPEAT_N_F(n, f, fn, ...) EXPAND(REVERSE_REPEAT_N_F_SEP(n, f, fn, COMMA_M, ##__VA_ARGS__))
#define REVERSE_REPEAT_N_F_ZERO(n, f, fn, ...) EXPAND(REVERSE_REPEAT_N_F_SEP_ZERO(n, f, fn, COMMA_M, ##__VA_ARGS__))

#define REPEAT_F_SEP(f, fn, sep, ...) EXPAND(REPEAT_N_F_SEP(DIV(EXPAND(NUM(##__VA_ARGS__)), fn), f, fn, sep, ##__VA_ARGS__))
#define REPEAT_F_SEP_ZERO(f, fn, sep, ...) EXPAND(REPEAT_N_F_SEP_ZERO(DIV(EXPAND(NUM(##__VA_ARGS__)), fn), f, fn, sep, ##__VA_ARGS__))
#define REVERSE_REPEAT_F_SEP(f, fn, sep, ...) EXPAND(REVERSE_REPEAT_N_F_SEP(DIV(EXPAND(NUM(##__VA_ARGS__)), fn), f, fn, sep, ##__VA_ARGS__))
#define REVERSE_REPEAT_F_SEP_ZERO(f, fn, sep, ...) EXPAND(REVERSE_REPEAT_N_F_SEP_ZERO(DIV(EXPAND(NUM(##__VA_ARGS__)), fn), f, fn, sep, ##__VA_ARGS__))

#define REPEAT_F(f, fn, ...) EXPAND(REPEAT_F_SEP(f, fn, COMMA_M, ##__VA_ARGS__))
#define REPEAT_F_ZERO(f, fn, ...) EXPAND(REPEAT_F_SEP_ZERO(f, fn, COMMA_M, ##__VA_ARGS__))
#define REVERSE_REPEAT_F(f, fn, ...) EXPAND(REVERSE_REPEAT_F_SEP(f, fn, COMMA_M, ##__VA_ARGS__))
#define REVERSE_REPEAT_F_ZERO(f, fn, ...) EXPAND(REVERSE_REPEAT_F_SEP_ZERO(f, fn, COMMA_M, ##__VA_ARGS__))

#define REPEAT_N(n, f, ...) EXPAND(REPEAT_N_F(n, f, 1, ##__VA_ARGS__))
#define REPEAT_N_ZERO(n, f, ...) EXPAND(REPEAT_N_F_ZERO(n, f, 1, ##__VA_ARGS__))
#define REVERSE_REPEAT_N(n, f, ...) EXPAND(REVERSE_REPEAT_N_F(n, f, 1, ##__VA_ARGS__))
#define REVERSE_REPEAT_N_ZERO(n, f, ...) EXPAND(REVERSE_REPEAT_N_F_ZERO(n, f, 1, ##__VA_ARGS__))

#define REPEAT(f, ...) EXPAND(REPEAT_F(f, 1, ##__VA_ARGS__))
#define REPEAT_ZERO(f, ...) EXPAND(REPEAT_F_ZERO(f, 1, ##__VA_ARGS__))
#define REVERSE_REPEAT(f, ...) EXPAND(REVERSE_REPEAT_F(f, 1, ##__VA_ARGS__))
#define REVERSE_REPEAT_ZERO(f, ...) EXPAND(REVERSE_REPEAT_F_ZERO(f, 1, ##__VA_ARGS__))

#define REPEAT_SEP(f, sep, ...) EXPAND(REPEAT_F_SEP(f, 1, sep, ##__VA_ARGS__))
#define REPEAT_SEP_ZERO(f, sep, ...) EXPAND(REPEAT_F_SEP_ZERO(f, 1, sep, ##__VA_ARGS__)
#define REVERSE_REPEAT_SEP(f, sep, ...) EXPAND(REVERSE_REPEAT_F_SEP(f, 1, sep, ##__VA_ARGS__)
#define REVERSE_REPEAT_SEP_ZERO(f, sep, ...) EXPAND(REVERSE_REPEAT_F_SEP_ZERO(f, 1, sep, ##__VA_ARGS__))

//#define _ADDSUB_F(n, X) n															   
//#define _SUB_CNT(...) EXPAND(GETARG(__VA_ARGS__))
//#define _ADD_CNT(...) EXPAND(NUM(__VA_ARGS__))

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

#define MUL__7(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__6(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__5(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__4(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__3(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__2(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__1(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL_0(X, Y, n) n						  
#define MUL_1(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_2(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_3(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_4(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_5(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_6(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_7(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL(X, Y) COMB(MUL_, X)(X, Y, 0)

#define DIV_0(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)						  
#define DIV_1(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
#define DIV_2(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
#define DIV_3(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
#define DIV_4(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
#define DIV_5(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
#define DIV_6(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
#define DIV_7(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
#define DIV(X, Y) MUL(DIV_0(ABS(X), ABS(Y), 0), MUL(SIGN(X), SIGN(Y)))

#define OR(X, Y) NO(EQ(ADD(IF(X), IF(Y)), 0))
#define AD(X, Y) EQ(ADD(IF(X), IF(Y)), 2)

#define GET_SAFE_1(var, ret, n, X, ...) var[X]
#define GET_SAFE_2(var, ret, n, X, ...) var[X] ? EXPAND(COMB(GET_SAFE_, DEC(n))((*var[X]), ret, DEC(n), __VA_ARGS__)) : ret
#define GET_SAFE_3(var, ret, n, X, ...) var[X] ? EXPAND(COMB(GET_SAFE_, DEC(n))((*var[X]), ret, DEC(n), __VA_ARGS__)) : ret
#define GET_SAFE_RET(var, ret, ...) (EXPAND(COMB(GET_SAFE_, EXPAND(NUM(__VA_ARGS__)))(var, ret, EXPAND(NUM(__VA_ARGS__)), __VA_ARGS__)))
#define GET_SAFE(var, ...) GET_SAFE_RET(var, 0, __VA_ARGS__)

#define EXIST_F(n, X) (EXCP_M((X)))
#define EXIST(ret, ...) if(EXPAND(REPEAT_SEP(EXIST_F, OR_M, __VA_ARGS__))) return ret;
#define EXIST_V(...) EXIST(void, __VA_ARGS__)
#define EXIST_B(...) EXIST(false, __VA_ARGS__)
#define EXIST_I(...) EXIST(0, __VA_ARGS__)


int main()
{
	cout << TO_STRING(MUL(0, 2)) << endl;
	cout << TO_STRING(MUL(2, 3)) << endl;
	cout << TO_STRING(MUL(2, 0)) << endl;
	cout << TO_STRING(MUL(3, 2)) << endl;
	cout << TO_STRING(MUL(_2, 0)) << endl;
	cout << TO_STRING(MUL(_3, 2)) << endl;
	cout << TO_STRING(MUL(_3, _2)) << endl;
	cout << "........." << endl;

	cout << TO_STRING(DIV(5, 2)) << endl;
	cout << TO_STRING(DIV(1, 3)) << endl;
	cout << TO_STRING(DIV(_5, 2)) << endl;
	cout << TO_STRING(DIV(1, _1)) << endl;
	cout << TO_STRING(DIV(0, 2)) << endl;
	cout << "........." << endl;

#define F1(n, X) COMB(X, n)
	//cout << TO_STRING(REPEAT_VA_2(1, 1, 2, F1, 1, RIS, SEM_M, a)) << endl;
	//cout << TO_STRING(REPEAT_N_F_SEP(2, F1, 1, SEM_M, a)) << endl;
	cout << TO_STRING(REPEAT_SEP(F1, SEM_M, a, b, c)) << endl;
	cout << TO_STRING(REPEAT(F1, a, b, c)) << endl;
	cout << TO_STRING(REPEAT_N(2, F1, a)) << endl;
	cout << TO_STRING(REPEAT_N(4, F1, a, b)) << endl;
	//cout << TO_STRING(REPEAT_N_F_ZERO(1, F1, 1, a, b, c)) << endl;
	//cout << TO_STRING(REPEAT_N_ZERO(1, F1, a, b, c)) << endl;
	cout << TO_STRING(REPEAT_N_ZERO(4, F1, a, b, c)) << endl;
	//cout << TO_STRING(REVERSE_REPEAT_N_F_SEP(4, F1, 1, COMMA_M, a)) << endl;
	//cout << TO_STRING(REVERSE_REPEAT_N_F(4, F1, 1, a)) << endl;
	cout << TO_STRING(REVERSE_REPEAT_N(4, F1, a)) << endl;
	cout << TO_STRING(REVERSE_REPEAT_N_ZERO(2, F1, a, b, c)) << endl;
	cout << TO_STRING(REVERSE_REPEAT_N_ZERO(3, F1, a, b, c)) << endl;
	cout << TO_STRING(REVERSE_REPEAT_N_ZERO(4, F1, a, b, c)) << endl;
	cout << "........." << endl;

#define  F2(n, X, Y) COMB(COMB(X, Y), n)
	cout << TO_STRING(REPEAT_N_F_SEP(4, F2, 2, SEM_M, a, b, c, d)) << endl;
	cout << TO_STRING(REPEAT_F_SEP(F2, 2, SEM_M, a, b, c, d)) << endl;
	cout << TO_STRING(REPEAT_F_SEP(F2, 2, SEM_M, a, b, c)) << endl;
	cout << TO_STRING(REPEAT_F(F2, 2, a, b, c, d)) << endl;
	//cout << TO_STRING(REPEAT_3(1, 2, 3, F2, 2, RIS, SEM_M, a, b, c, d)) << endl;
	cout << TO_STRING(REPEAT_N_F(3, F2, 2, a, b)) << endl;
	cout << TO_STRING(REPEAT_N_F(3, F2, 2, a, b, c)) << endl;
	cout << TO_STRING(REPEAT_N_F(3, F2, 2, a)) << endl;
	cout << TO_STRING(REPEAT_N_F(4, F2, 2, a, b, c, d)) << endl;
	cout << TO_STRING(REPEAT_N_F_ZERO(4, F2, 2, a, b, c, d)) << endl;
	cout << TO_STRING(REVERSE_REPEAT_N_F(4, F2, 2, a, b, c, d)) << endl;
	cout << TO_STRING(REVERSE_REPEAT_N_F_ZERO(4, F2, 2, a, b, c, d)) << endl;
	cout << "........." << endl;

	cout << TO_STRING(EXIST(*this, a, b, c, d)) << endl;
	cout << TO_STRING(GET_SAFE(a, 1, 2, 3)) << endl;
	cout << "........." << endl;

#define  F3(n, X, Y, Z) COMB(COMB(COMB(X, Y), Z), n)
// #define F3_FUNC(...) EXPAND(F3(__VA_ARGS__))
	//cout << TO_STRING(CUTARGS_B(3, a, b, c)) << endl;
	//cout << TO_STRING(F3(1, a, b, c)) << endl;
	//cout << TO_STRING(F3_FUNC(1, CUTARGS_B(3, a, b, c))) << endl;
	cout << TO_STRING(REPEAT_1(1, 1, 1, F3, 3, RIS, SEM_M, a, b, c)) << endl;
	//cout << TO_STRING(REPEAT_N_F_SEP(1, F3, 3, SEM_M, a, b, c)) << endl;
	//cout << TO_STRING(REPEAT_F_SEP(F3, 3, SEM_M, a, b, c)) << endl;
	enum uValueType
	{
		uValueType_Void,
		uValueType_Int,
		uValueType_Uint,
		uValueType_Int64,
		uValueType_Uint64,
		uValueType_Float,
		uValueType_Double,
		uValueType_String,
	};
#define RESET(X) if(type != X) reset(X);
#define OPERATOR_EQUAL_F(n, type_name, tp, va) \
		uValue& operator=(const tp& t)\
		{\
			RESET(type_name)\
			va = t;\
			return *this;\
		}
#define OPERATOR_EQUAL(...) EXPAND(REPEAT_F_SEP(OPERATOR_EQUAL_F, 3, SEM_M, ##__VA_ARGS__))
	cout << TO_STRING(OPERATOR_EQUAL(uValueType_Int, int, v.i)) << endl;

	return 0;
}