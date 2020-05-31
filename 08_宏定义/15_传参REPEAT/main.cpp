#include <iostream>

using namespace std;

#define EXPAND(...) __VA_ARGS__
#define EXPAND_F(F, ...) EXPAND(F(__VA_ARGS__))

#define TO_STRING(X) TO_STRING1(X)
#define TO_STRING1(X) #X

#define COMB(X, Y) COMB1(X, Y)
#define COMB1(X, Y) X##Y

#define SIGN__29 _1
#define SIGN__28 _1
#define SIGN__27 _1
#define SIGN__26 _1
#define SIGN__25 _1
#define SIGN__24 _1
#define SIGN__23 _1
#define SIGN__22 _1
#define SIGN__21 _1
#define SIGN__20 _1
#define SIGN__19 _1
#define SIGN__18 _1
#define SIGN__17 _1
#define SIGN__16 _1
#define SIGN__15 _1
#define SIGN__14 _1
#define SIGN__13 _1
#define SIGN__12 _1
#define SIGN__11 _1
#define SIGN__10 _1
#define SIGN__9 _1
#define SIGN__8 _1
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
#define SIGN_8 1
#define SIGN_9 1
#define SIGN_10 1
#define SIGN_11 1
#define SIGN_12 1
#define SIGN_13 1
#define SIGN_14 1
#define SIGN_15 1
#define SIGN_16 1
#define SIGN_17 1
#define SIGN_18 1
#define SIGN_19 1
#define SIGN_20 1
#define SIGN_21 1
#define SIGN_22 1
#define SIGN_23 1
#define SIGN_24 1
#define SIGN_25 1
#define SIGN_26 1
#define SIGN_27 1
#define SIGN_28 1
#define SIGN_29 1
#define SIGN(n) COMB(SIGN_, n)

#define OPP__29 29
#define OPP__28 28
#define OPP__27 27
#define OPP__26 26
#define OPP__25 25
#define OPP__24 24
#define OPP__23 23
#define OPP__22 22
#define OPP__21 21
#define OPP__20 20
#define OPP__19 19
#define OPP__18 18
#define OPP__17 17
#define OPP__16 16
#define OPP__15 15
#define OPP__14 14
#define OPP__13 13
#define OPP__12 12
#define OPP__11 11
#define OPP__10 10
#define OPP__9 9
#define OPP__8 8
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
#define OPP_8 _8
#define OPP_9 _9
#define OPP_10 _10
#define OPP_11 _11
#define OPP_12 _12
#define OPP_13 _13
#define OPP_14 _14
#define OPP_15 _15
#define OPP_16 _16
#define OPP_17 _17
#define OPP_18 _18
#define OPP_19 _19
#define OPP_20 _20
#define OPP_21 _21
#define OPP_22 _22
#define OPP_23 _23
#define OPP_24 _24
#define OPP_25 _25
#define OPP_26 _26
#define OPP_27 _27
#define OPP_28 _28
#define OPP_29 _29
#define OPP(n) COMB(OPP_, n)
#define ABS(n) SWITCH_CASE(EQ(SIGN(n), _1), n, OPP(n))

#define COMMA_M(X) ,X
#define SEM_M(X) ;X
#define EXCP_M(X) !X
#define OR_M(X) ||X
#define UDRL_M(X) COMB(_, X)

#define DEC__29 _30
#define DEC__28 _29
#define DEC__27 _28
#define DEC__26 _27
#define DEC__25 _26
#define DEC__24 _25
#define DEC__23 _24
#define DEC__22 _23
#define DEC__21 _22
#define DEC__20 _21
#define DEC__19 _20
#define DEC__18 _19
#define DEC__17 _18
#define DEC__16 _17
#define DEC__15 _16
#define DEC__14 _15
#define DEC__13 _14
#define DEC__12 _13
#define DEC__11 _12
#define DEC__10 _11
#define DEC__9 _10
#define DEC__8 _9 
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
#define DEC_8 7
#define DEC_9 8
#define DEC_10 9
#define DEC_11 10
#define DEC_12 11
#define DEC_13 12
#define DEC_14 13
#define DEC_15 14
#define DEC_16 15
#define DEC_17 16
#define DEC_18 17
#define DEC_19 18
#define DEC_20 19
#define DEC_21 20
#define DEC_22 21
#define DEC_23 22
#define DEC_24 23
#define DEC_25 24
#define DEC_26 25
#define DEC_27 26
#define DEC_28 27
#define DEC_29 28
#define DEC(n) COMB(DEC_, n)

#define RIS__29 _28
#define RIS__28 _27
#define RIS__27 _26
#define RIS__26 _25
#define RIS__25 _24
#define RIS__24 _23
#define RIS__23 _22
#define RIS__22 _21
#define RIS__21 _20
#define RIS__20 _19
#define RIS__19 _18
#define RIS__18 _17
#define RIS__17 _16
#define RIS__16 _15
#define RIS__15 _14
#define RIS__14 _13
#define RIS__13 _12
#define RIS__12 _11
#define RIS__11 _10
#define RIS__10 _9
#define RIS__9 _8
#define RIS__8 _7
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
#define RIS_6 7
#define RIS_7 8
#define RIS_8 9
#define RIS_9 10
#define RIS_10 11
#define RIS_11 12
#define RIS_12 13
#define RIS_13 14
#define RIS_14 15
#define RIS_15 16
#define RIS_16 17
#define RIS_17 18
#define RIS_18 19
#define RIS_19 20
#define RIS_20 21
#define RIS_21 22
#define RIS_22 23
#define RIS_23 24
#define RIS_24 25
#define RIS_25 26
#define RIS_26 27
#define RIS_27 28
#define RIS_28 29
#define RIS_29 30
#define RIS(n) COMB(RIS_, n)

//#define REPEAT_1(first, num, func, sort, X) func(first, X)
//#define REPEAT_2(first, num, func, sort, X) COMB(func(first, X), COMMA(COMB(REPEAT_, DEC(num))(sort(first), DEC(num), func, sort, X)))
//#define REPEAT_3(first, num, func, sort, X) COMB(func(first, X), COMMA(COMB(REPEAT_, DEC(num))(sort(first), DEC(num), func, sort, X)))

//#define REPEAT(n, f, X) COMB(REPEAT_, n)(1, n, f, RIS, X)

#define GETARG_0(n, func, X, ...) EXPAND(func(X, X, ##__VA_ARGS__))
#define GETARG_1(n, func, X, ...) EXPAND(func(X, ##__VA_ARGS__))
#define GETARG_2(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_3(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_4(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_5(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_6(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_7(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_8(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_9(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_10(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_11(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_12(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_13(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_14(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_15(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_16(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_17(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_18(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_19(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_20(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_21(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_22(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_23(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_24(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_25(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_26(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_27(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_28(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))
#define GETARG_29(n, func, X, ...) EXPAND(COMB(GETARG_, DEC(n))(DEC(n), func, __VA_ARGS__))

#define GETARG_F(X, ...) X
#define GETARG(N, ...) EXPAND(COMB(GETARG_, N)(N, GETARG_F, __VA_ARGS__))

#define CUTARGS_F(X, ...) __VA_ARGS__
#define CUTARGS(N, ...) EXPAND(COMB(GETARG_, N)(N, CUTARGS_F, __VA_ARGS__))

#define CUTARGS_B_0(n, X, ...) X
#define CUTARGS_B_1(n, X, ...) X
#define CUTARGS_B_2(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_3(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_4(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_5(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_6(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_7(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_8(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_9(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_10(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_11(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_12(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_13(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_14(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_15(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_16(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_17(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_18(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_19(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_20(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_21(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_22(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_23(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_24(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_25(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_26(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_27(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_28(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B_29(n, X, ...) COMB(X, COMMA_M(COMB(CUTARGS_B_, DEC(n))(DEC(n), ##__VA_ARGS__)))
#define CUTARGS_B(N, ...) EXPAND(COMB(CUTARGS_B_, N)(N, ##__VA_ARGS__))
#define CUTARGS_C(B, E, ...) EXPAND(CUTARGS(1, EXPAND(CUTARGS_B(RIS(B), X, ##__VA_ARGS__)), EXPAND(CUTARGS(RIS(E), X, ##__VA_ARGS__))))

#define SWITCH_CASE(conf, ...) EXPAND(GETARG(RIS(conf), ##__VA_ARGS__))
#define SWITCH_CASE_ARGS_N_R_F(b, e, ...) EXPAND(CUTARGS_B(e, ##__VA_ARGS__))
#define SWITCH_CASE_ARGS_N_R(conf, b, e, ...) EXPAND_F(COMB(GETARG_, RIS(conf))(RIS(conf), GETARG_F, SWITCH_CASE_ARGS_N_R_F, CUTARGS_C), b, e, ##__VA_ARGS__)
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

#define _NUM(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19,_20, _21, _22, _23, _24, _25, _26, _27, _28, _29, N, ...) N
#define _NUM_ARGS() 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define _NUM_ARGS_CNT(...) EXPAND(_NUM(__VA_ARGS__))
#define NUM(...) EXPAND(_NUM_ARGS_CNT(0, ##__VA_ARGS__, _NUM_ARGS()))

//#define REPEAT_FUNC(func, ...) EXPAND(func(__VA_ARGS__))
#define REPEAT_1(first, num, total, func, funcN, argsN, sort, sep, ...) EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__)))))																		  
#define REPEAT_2(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_3(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_4(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_5(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_6(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_7(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_8(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_9(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_10(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_11(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_12(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_13(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_14(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_15(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_16(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_17(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_18(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_19(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_20(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_21(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_22(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_23(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_24(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_25(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_26(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_27(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_28(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))
#define REPEAT_29(first, num, total, func, funcN, argsN, sort, sep, ...) COMB(EXPAND_F(func, first, EXPAND(CUTARGS_B(ADD(funcN, argsN), EXPAND(CUTARGS_B(funcN, EXPAND(CUTARGS(argsN, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(argsN, ##__VA_ARGS__))))), sep(COMB(REPEAT_, DEC(total))(sort(first), SWITCH_CASE(LE(num, 1), DEC(num), 1), DEC(total), func, funcN, argsN, sort, sep, SWITCH_CASE_ARGS_N_R(GT(num, 1), argsN, ADD(funcN, argsN), ##__VA_ARGS__))))

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
#define REPEAT_N_F_A_SEP(n, f, fn, an, sep, ...) COMB(REPEAT_, n)(1, DIV(EXPAND(NUM(CUTARGS(an, ##__VA_ARGS__))), fn), n, f, fn, an, RIS, sep, ##__VA_ARGS__)
#define REPEAT_N_F_A_SEP_ZERO(n, f, fn, an, sep, ...) COMB(EXPAND_F(f, 0, EXPAND(CUTARGS_B(ADD(fn, an), EXPAND(CUTARGS_B(fn, EXPAND(CUTARGS(an, ##__VA_ARGS__)))), EXPAND(CUTARGS_B(an, ##__VA_ARGS__))))), sep(REPEAT_N_F_A_SEP(DEC(n), f, fn, an, sep, CUTARGS_C(an, ADD(an, fn), ##__VA_ARGS__))))
#define REVERSE_REPEAT_N_F_A_SEP(n, f, fn, an, sep, ...) COMB(REPEAT_, n)(n, DIV(EXPAND(NUM(CUTARGS(an, ##__VA_ARGS__))), fn), n, f, fn, an, DEC, sep, ##__VA_ARGS__)
#define REVERSE_REPEAT_N_F_A_SEP_ZERO(n, f, fn, an, sep, ...) COMB(REVERSE_REPEAT_N_F_A_SEP(DEC(n), f, fn, an, sep, ##__VA_ARGS__), sep(EXPAND_F(f, 0, CUTARGS_B(fn, CUTARGS(ADD(an, MUL(fn, DEC(MIN(n, DIV(EXPAND(NUM(CUTARGS(an, ##__VA_ARGS__))), fn))))), ##__VA_ARGS__)), CUTARGS_B(an, ##__VA_ARGS__)))) 

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
#define REPEAT_N_F_A(n, f, fn, an, ...) REPEAT_N_F_A_SEP(n, f, fn, an, COMMA_M, ##__VA_ARGS__)
#define REPEAT_N_F_A_ZERO(n, f, fn, an, ...) REPEAT_N_F_A_SEP_ZERO(n, f, fn, an, COMMA_M, ##__VA_ARGS__)
#define REVERSE_REPEAT_N_F_A(n, f, fn, an, ...) REVERSE_REPEAT_N_F_A_SEP(n, f, fn, an, COMMA_M, ##__VA_ARGS__)
#define REVERSE_REPEAT_N_F_A_ZERO(n, f, fn, an, ...) REVERSE_REPEAT_N_F_A_SEP_ZERO(n, f, fn, an, COMMA_M, ##__VA_ARGS__)

#define REPEAT_N_F_SEP(n, f, fn, sep, ...) REPEAT_N_F_A_SEP(n, f, fn, 0, sep, ##__VA_ARGS__)
#define REPEAT_N_F_SEP_ZERO(n, f, fn, sep, ...) REPEAT_N_F_A_SEP_ZERO(n, f, fn, 0, sep, ##__VA_ARGS__)
#define REVERSE_REPEAT_N_F_SEP(n, f, fn, sep, ...) REVERSE_REPEAT_N_F_A_SEP(n, f, fn, 0, sep, ##__VA_ARGS__)
#define REVERSE_REPEAT_N_F_SEP_ZERO(n, f, fn, sep, ...) REVERSE_REPEAT_N_F_A_SEP_ZERO(n, f, fn, 0, sep, ##__VA_ARGS__)

#define REPEAT_N_A_SEP(n, f, an, sep, ...) REPEAT_N_F_A_SEP(n, f, 1, an, sep, ##__VA_ARGS__)
#define REPEAT_N_A_SEP_ZERO(n, f, an, sep, ...) REPEAT_N_F_A_SEP_ZERO(n, f, 1, an, sep, ##__VA_ARGS__)
#define REVERSE_REPEAT_N_A_SEP(n, f, an, sep, ...) REVERSE_REPEAT_N_F_A_SEP(n, f, 1, an, sep, ##__VA_ARGS__)
#define REVERSE_REPEAT_N_A_SEP_ZERO(n, f, an, sep, ...) REVERSE_REPEAT_N_F_A_SEP_ZERO(n, f, 1, an, sep, ##__VA_ARGS__)

#define REPEAT_F_A_SEP(f, fn, an, sep, ...) REPEAT_N_F_A_SEP(DIV(EXPAND(NUM(CUTARGS(an, ##__VA_ARGS__))), fn), f, fn, an, sep, ##__VA_ARGS__)
#define REPEAT_F_A_SEP_ZERO(f, fn, an, sep, ...) REPEAT_N_F_A_SEP_ZERO(DIV(EXPAND(NUM(CUTARGS(an, ##__VA_ARGS__))), fn), f, fn, an, sep, ##__VA_ARGS__)
#define REVERSE_REPEAT_F_A_SEP(f, fn, an, sep, ...) REVERSE_REPEAT_N_F_A_SEP(DIV(EXPAND(NUM(CUTARGS(an, ##__VA_ARGS__))), fn), f, fn, an, sep, ##__VA_ARGS__)
#define REVERSE_REPEAT_F_A_SEP_ZERO(f, fn, an, sep, ...) REVERSE_REPEAT_N_F_A_SEP_ZERO(DIV(EXPAND(NUM(CUTARGS(an, ##__VA_ARGS__))), fn), f, fn, an, sep, ##__VA_ARGS__)

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
#define REPEAT_N_F(n, f, fn, ...) REPEAT_N_F_A(n, f, fn, 0, ##__VA_ARGS__)
#define REPEAT_N_F_ZERO(n, f, fn, ...) REPEAT_N_F_A_ZERO(n, f, fn, 0, ##__VA_ARGS__)
#define REVERSE_REPEAT_N_F(n, f, fn, ...) REVERSE_REPEAT_N_F_A(n, f, fn, 0, ##__VA_ARGS__)
#define REVERSE_REPEAT_N_F_ZERO(n, f, fn, ...) REVERSE_REPEAT_N_F_A_ZERO(n, f, fn, 0, ##__VA_ARGS__)

#define REPEAT_N_A(n, f, an, ...) REPEAT_N_F_A(n, f, 1, an, ##__VA_ARGS__)
#define REPEAT_N_A_ZERO(n, f, an, ...) REPEAT_N_F_A_ZERO(n, f, 1, an, ##__VA_ARGS__)
#define REVERSE_REPEAT_N_A(n, f, an, ...) REVERSE_REPEAT_N_F_A(n, f, 1, an, ##__VA_ARGS__)
#define REVERSE_REPEAT_N_A_ZERO(n, f, an, ...) REVERSE_REPEAT_N_F_A_ZERO(n, f, 1, an, ##__VA_ARGS__)

#define REPEAT_N_SEP(n, f, sep, ...) REPEAT_N_F_SEP(n, f, 1, sep, ##__VA_ARGS__)								  //
#define REPEAT_N_SEP_ZERO(n, f, sep, ...) REPEAT_N_F_SEP_ZERO(n, f, 1, sep, ##__VA_ARGS__)						  //
#define REVERSE_REPEAT_N_SEP(n, f, sep, ...) REVERSE_REPEAT_N_F_SEP(n, f, 1, sep, ##__VA_ARGS__)				  //
#define REVERSE_REPEAT_N_SEP_ZERO(n, f, sep, ...) REVERSE_REPEAT_N_F_SEP_ZERO(n, f, 1, sep, ##__VA_ARGS__)		  //

#define REPEAT_F_A(f, fn, an, ...) REPEAT_F_A_SEP(f, fn, an, COMMA_M, ##__VA_ARGS__)							  //
#define REPEAT_F_A_ZERO(f, fn, an, ...) REPEAT_F_A_SEP_ZERO(f, fn, an, COMMA_M, ##__VA_ARGS__)
#define REVERSE_REPEAT_F_A(f, fn, an, ...) REVERSE_REPEAT_F_A_SEP(f, fn, an, COMMA_M, ##__VA_ARGS__)
#define REVERSE_REPEAT_F_A_ZERO(f, fn, an, ...) REVERSE_REPEAT_F_A_SEP_ZERO(f, fn, an, COMMA_M, ##__VA_ARGS__)

#define REPEAT_F_SEP(f, fn, sep, ...) REPEAT_F_A_SEP(f, fn, 0, sep, ##__VA_ARGS__)								  //
#define REPEAT_F_SEP_ZERO(f, fn, sep, ...) REPEAT_F_A_SEP_ZERO(f, fn, 0, sep, ##__VA_ARGS__)
#define REVERSE_REPEAT_F_SEP(f, fn, sep, ...) REVERSE_REPEAT_F_A_SEP(f, fn, 0, sep, ##__VA_ARGS__)
#define REVERSE_REPEAT_F_SEP_ZERO(f, fn, sep, ...) REVERSE_REPEAT_F_A_SEP_ZERO(f, fn, 0, sep, ##__VA_ARGS__)

#define REPEAT_A_SEP(f, an, sep, ...) REPEAT_F_A_SEP(f, 1, an, sep, ##__VA_ARGS__)
#define REPEAT_A_SEP_ZERO(f, an, sep, ...) REPEAT_F_A_SEP_ZERO(f, 1, an, sep, ##__VA_ARGS__)
#define REVERSE_REPEAT_A_SEP(f, an, sep, ...) REVERSE_REPEAT_F_A_SEP(f, 1, an, sep, ##__VA_ARGS__)
#define REVERSE_REPEAT_A_SEP_ZERO(f, an, sep, ...) REVERSE_REPEAT_F_A_SEP_ZERO(f, 1, an, sep, ##__VA_ARGS__)

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
#define REPEAT_N(n, f, ...) REPEAT_N_F(n, f, 1, ##__VA_ARGS__) 													  //
#define REPEAT_N_ZERO(n, f, ...) REPEAT_N_F_ZERO(n, f, 1, ##__VA_ARGS__) 										  //
#define REVERSE_REPEAT_N(n, f, ...) REVERSE_REPEAT_N_F(n, f, 1, ##__VA_ARGS__) 									  //
#define REVERSE_REPEAT_N_ZERO(n, f, ...)REVERSE_REPEAT_N_F_ZERO(n, f, 1, ##__VA_ARGS__)							  //

#define REPEAT_F(f, fn, ...) REPEAT_F_SEP(f, fn, COMMA_M, ##__VA_ARGS__) 										  //
#define REPEAT_F_ZERO(f, fn, ...) REPEAT_F_SEP_ZERO(f, fn, COMMA_M, ##__VA_ARGS__) 								  //
#define REVERSE_REPEAT_F(f, fn, ...) REVERSE_REPEAT_F_SEP(f, fn, COMMA_M, ##__VA_ARGS__) 						  //
#define REVERSE_REPEAT_F_ZERO(f, fn, ...)REVERSE_REPEAT_F_SEP_ZERO(f, fn, COMMA_M, ##__VA_ARGS__)				  //

#define REPEAT_A(f, an, ...) REPEAT_A_SEP(f, an, COMMA_M, ##__VA_ARGS__) 										  //
#define REPEAT_A_ZERO(f, an, ...) REPEAT_A_SEP_ZERO(f, an, COMMA_M, ##__VA_ARGS__)								  //
#define REVERSE_REPEAT_A(f, an, ...) REVERSE_REPEAT_A_SEP(f, an, COMMA_M, ##__VA_ARGS__) 
#define REVERSE_REPEAT_A_ZERO(f, an, ...)REVERSE_REPEAT_A_SEP_ZERO(f, an, COMMA_M, ##__VA_ARGS__)

#define REPEAT_SEP(f, sep, ...) REPEAT_A_SEP(f, 0, sep, ##__VA_ARGS__) 											  //
#define REPEAT_SEP_ZERO(f, sep, ...) REPEAT_A_SEP_ZERO(f, 0, sep, ##__VA_ARGS__)								  //
#define REVERSE_REPEAT_SEP(f, sep, ...) REVERSE_REPEAT_A_SEP(f, 0, sep, ##__VA_ARGS__) 							  //
#define REVERSE_REPEAT_SEP_ZERO(f, sep, ...)REVERSE_REPEAT_A_SEP_ZERO(f, 0, sep, ##__VA_ARGS__)					  //

#define REPEAT(f, ...) REPEAT_SEP(f, COMMA_M, ##__VA_ARGS__) 													  //
#define REPEAT_ZERO(f, ...) REPEAT_SEP_ZERO(f, COMMA_M, ##__VA_ARGS__) 											  //
#define REVERSE_REPEAT(f, ...) REVERSE_REPEAT_SEP(f, COMMA_M, ##__VA_ARGS__) 									  //
#define REVERSE_REPEAT_ZERO(f, ...) REVERSE_REPEAT_SEP_ZERO(f, COMMA_M, ##__VA_ARGS__) 							  //

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

//#define _ADDSUB_F(n, X) n															   
//#define _SUB_CNT(...) EXPAND(GETARG(__VA_ARGS__))
//#define _ADD_CNT(...) EXPAND(NUM(__VA_ARGS__))

//#define ADD(X, Y) _ADD_CNT(REPEAT(Y, _ADDSUB_F), REPEAT(X, _ADDSUB_F))
//#define ADD(X, Y) RIS(GETARG(Y, COMB(REPEAT_, Y)(X, Y, _ADDSUB_F, RIS, COMMA)))
#define ADD__29(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__28(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__27(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__26(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__25(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__24(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__23(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__22(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__21(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__20(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__19(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__18(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__17(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__16(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__15(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__14(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__13(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__12(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__11(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__10(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__9(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
#define ADD__8(X, Y) COMB(ADD_, RIS(X))(RIS(X), DEC(Y))
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
#define ADD_8(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_9(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_10(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_11(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_12(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_13(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_14(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_15(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_16(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_17(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_18(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_19(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_20(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_21(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_22(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_23(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_24(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_25(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_26(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_27(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_28(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD_29(X, Y) COMB(ADD_, DEC(X))(DEC(X), RIS(Y))
#define ADD(X, Y) COMB(ADD_, X)(X, Y)
//#define SUB(X, Y) _SUB_CNT(RIS(RIS(X)), REPEAT_ZERO(Y, _ADDSUB_F), REPEAT_ZERO(X, _ADDSUB_F))
//#define SUB(X, Y) DEC(GETARG(Y, COMB(REPEAT_, Y)(X, Y, _ADDSUB_F, DEC, COMMA)))
#define SUB(X, Y) COMB(ADD_, X)(X, OPP(Y))

#define MUL__29(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__28(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__27(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__26(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__25(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__24(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__23(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__22(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__21(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__20(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__19(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__18(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__17(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__16(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__15(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__14(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__13(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__12(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__11(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__10(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__9(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
#define MUL__8(X, Y, n) COMB(MUL_, RIS(X))(RIS(X), Y, SUB(n, Y))
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
#define MUL_8(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_9(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_10(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_11(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_12(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_13(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_14(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_15(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_16(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_17(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_18(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_19(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_20(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_21(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_22(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_23(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_24(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_25(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_26(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_27(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_28(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL_29(X, Y, n) COMB(MUL_, DEC(X))(DEC(X), Y, ADD(n, Y))
#define MUL(X, Y) COMB(MUL_, X)(X, Y, 0)

#define DIV_0(X, Y, n) SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_1(X, Y, n) SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_2(X, Y, n) SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_3(X, Y, n) SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_4(X, Y, n) SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_5(X, Y, n) SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_6(X, Y, n) SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_7(X, Y, n) SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_8(X, Y, n) SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_9(X, Y, n) SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_10(X, Y, n) SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_11(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_12(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_13(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_14(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_15(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_16(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_17(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_18(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_19(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_20(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_21(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_22(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_23(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_24(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_25(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_26(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_27(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_28(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV_29(X, Y, n)	SWITCH_CASE(GE(X, Y), n, COMB(DIV_, SUB(X, Y))(SUB(X, Y), Y, RIS(n)))
#define DIV(X, Y) MUL(COMB(DIV_, ABS(X))(ABS(X), ABS(Y), 0), MUL(SIGN(X), SIGN(Y)))

//#define DIV_0(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)						  
//#define DIV_1(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_2(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_3(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_4(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_5(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_6(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_7(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_8(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_9(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_10(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)						  
//#define DIV_11(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_12(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_13(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_14(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_15(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_16(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_17(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_18(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_19(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_20(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)						  
//#define DIV_21(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_22(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_23(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_24(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_25(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_26(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_27(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_28(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV_29(X, Y, n) SWITCH_CASE(LS(X, Y), COMB(DIV_, RIS(n))(SUB(X, Y), Y, RIS(n)), n)
//#define DIV(X, Y) MUL(DIV_0(ABS(X), ABS(Y), 0), MUL(SIGN(X), SIGN(Y)))

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
	cout << "1..........................................................................." << endl;
#define F1(n, X) COMB(X, n)
	cout << TO_STRING(REPEAT、REPEAT_ZERO、REVERSE_REPEAT、REVERSE_REPEAT_ZERO) << endl;
	//cout << TO_STRING(REPEAT_A_SEP(F1, 0, COMMA_M, a, b, c)) << endl;
	//cout << TO_STRING(REPEAT_SEP(F1, COMMA_M, a, b, c)) << endl;
	cout << TO_STRING(REPEAT(F1, a, b, c)) << endl;
	cout << TO_STRING(REPEAT_ZERO(F1, a, b, c)) << endl;
	cout << TO_STRING(REVERSE_REPEAT(F1, a, b, c)) << endl;
	cout << TO_STRING(REVERSE_REPEAT_ZERO(F1, a, b, c)) << endl;
	cout << TO_STRING(REPEAT_SEP、REPEAT_SEP_ZERO、REVERSE_REPEAT_SEP、REVERSE_REPEAT_SEP_ZERO) << endl;
	cout << TO_STRING(REPEAT_SEP(F1, SEM_M, a, b, c)) << endl;
	cout << TO_STRING(REPEAT_SEP_ZERO(F1,  EXCP_M, a, b, c)) << endl;
	cout << TO_STRING(REVERSE_REPEAT_SEP(F1, OR_M, a, b, c)) << endl;
	cout << TO_STRING(REVERSE_REPEAT_SEP_ZERO(F1, UDRL_M, a, b, c)) << endl;
	cout << TO_STRING(REPEAT_N、REPEAT_N_ZERO、REVERSE_REPEAT_N、REVERSE_REPEAT_N_ZERO) << endl;
	cout << TO_STRING(REPEAT_N(1, F1, a, b, c)) << endl;
	cout << TO_STRING(REPEAT_N_ZERO(2, F1, a, b, c)) << endl;
	cout << TO_STRING(REVERSE_REPEAT_N(3, F1, a, b, c)) << endl;
	cout << TO_STRING(REVERSE_REPEAT_N_ZERO(4, F1, a, b, c)) << endl;
	cout << TO_STRING(REPEAT_N_SEP、REPEAT_N_SEP_ZERO、REVERSE_REPEAT_N_SEP、REVERSE_REPEAT_N_SEP_ZERO) << endl;
	cout << TO_STRING(REPEAT_N_SEP(1, F1, SEM_M, a, b, c)) << endl;
	cout << TO_STRING(REPEAT_N_SEP_ZERO(2, F1, EXCP_M, a, b, c)) << endl;
	cout << TO_STRING(REVERSE_REPEAT_N_SEP(3, F1, OR_M, a, b, c)) << endl;
	cout << TO_STRING(REVERSE_REPEAT_N_SEP_ZERO(4, F1, UDRL_M, a, b, c)) << endl;

	////cout << TO_STRING(EXPAND(CUTARGS_B(1, CUTARGS(0, a)))) << endl;
	//cout << TO_STRING(REPEAT_FUNC(F1, 1, a, )) << endl;
	//cout << TO_STRING(EXPAND(CUTARGS_B(0, a)) << endl;
	//cout << TO_STRING(EXPAND_F(F1, 1, EXPAND(CUTARGS_B(ADD(1, 0), EXPAND(CUTARGS_B(1, CUTARGS(0, a))), EXPAND(CUTARGS_B(0, a)))))) << endl;
	//cout << TO_STRING(REPEAT_1(1, 1, 1, F1, 1, 0, RIS, COMMA_M, a)) << endl;
	//cout << TO_STRING(REPEAT_2(1, 1, 2, F1, 1, 0, RIS, COMMA_M, a)) << endl;
	//cout << ". . . . . . . ." << endl;
	//cout << TO_STRING(REPEAT_VA_2(1, 1, 2, F1, 1, RIS, SEM_M, a)) << endl;
//cout << TO_STRING(REPEAT_N_F_SEP(2, F1, 1, SEM_M, a)) << endl;
	//cout << TO_STRING(REPEAT_SEP(F1, SEM_M, a, b, c)) << endl;
	//cout << TO_STRING(REPEAT(F1, a, b, c)) << endl;
	//cout << TO_STRING(REPEAT_N(2, F1, a)) << endl;
	//cout << TO_STRING(REPEAT_N(4, F1, a, b)) << endl;
	//cout << TO_STRING(REPEAT_N_F_ZERO(1, F1, 1, a, b, c)) << endl;
	//cout << TO_STRING(REPEAT_N_ZERO(1, F1, a, b, c)) << endl;
	//cout << TO_STRING(REPEAT_N_ZERO(4, F1, a, b, c)) << endl;
	//cout << TO_STRING(REVERSE_REPEAT_N_F_SEP(4, F1, 1, COMMA_M, a)) << endl;
	//cout << TO_STRING(REVERSE_REPEAT_N_F(4, F1, 1, a)) << endl;
	//cout << TO_STRING(REVERSE_REPEAT_N(4, F1, a)) << endl;
	//cout << TO_STRING(REVERSE_REPEAT_N_ZERO(2, F1, a, b, c)) << endl;
	//cout << TO_STRING(REVERSE_REPEAT_N_ZERO(3, F1, a, b, c)) << endl;
	//cout << TO_STRING(REVERSE_REPEAT_N_ZERO(4, F1, a, b, c)) << endl;

	cout << "2..........................................................................." << endl;
#define F2(n, X, Y) COMB(Y, UDRL_M(COMB(X, n)))
#define F21(n, X, Y) COMB(COMB(X, Y), n)
	cout << TO_STRING(REPEAT_A) << endl;
	cout << TO_STRING(REPEAT_A(F2, 1, T, a, b, c)) << endl;
	cout << TO_STRING(REPEAT_F、REPEAT_F_ZERO、REVERSE_REPEAT_F、REVERSE_REPEAT_F_ZERO) << endl;
	cout << TO_STRING(REPEAT_F(F21, 2, a, b, c)) << endl;
	cout << TO_STRING(REPEAT_F_ZERO(F21, 2, a, b, c, d)) << endl;
	cout << TO_STRING(REVERSE_REPEAT_F(F21, 3, a, b, c, d)) << endl;
	cout << TO_STRING(REVERSE_REPEAT_F_ZERO(F21, 2, a, b, c, d, e)) << endl;


	//cout << TO_STRING(REPEAT_1(1, 1, 1, F2, 1, 1, RIS, COMMA_M, T, a, b)) << endl;
	//cout << TO_STRING(REPEAT_N_F_A_SEP(2, F2, 1, 1, COMMA_M, T, a)) << endl;
	//cout << TO_STRING(REPEAT_N_F_A_SEP_ZERO(4, F2, 1, 1, COMMA_M, T, a, b, c)) << endl;
	//cout << TO_STRING(REVERSE_REPEAT_N_F_A_SEP(4, F2, 1, 1, COMMA_M, T, a, b, c)) << endl;
	//cout << TO_STRING(REVERSE_REPEAT_N_F_A_SEP_ZERO(4, F2, 1 ,1, COMMA_M, T, a, b, c, d)) << endl;
	//cout << ". . . . . . . ." << endl;
	//cout << TO_STRING(REPEAT_N_F_SEP(4, F21, 2, SEM_M, a, b, c, d)) << endl;
	//cout << TO_STRING(REPEAT_F_SEP(F21, 2, SEM_M, a, b, c, d)) << endl;
	//cout << TO_STRING(REPEAT_F_SEP(F21, 2, SEM_M, a, b, c)) << endl;
	//cout << TO_STRING(REPEAT_F(F21, 2, a, b, c, d)) << endl;
	//cout << TO_STRING(REPEAT_3(1, 2, 3, F2, 2, RIS, SEM_M, a, b, c, d)) << endl;
	//cout << TO_STRING(REPEAT_N_F(3, F21, 2, a, b)) << endl;
	//cout << TO_STRING(REPEAT_N_F(3, F21, 2, a, b, c)) << endl;
	//cout << TO_STRING(REPEAT_N_F(3, F21, 2, a)) << endl;
	//cout << TO_STRING(REPEAT_N_F(4, F21, 2, a, b, c, d)) << endl;
	//cout << TO_STRING(REPEAT_N_F_ZERO(4, F21, 2, a, b, c, d)) << endl;
	//cout << TO_STRING(REVERSE_REPEAT_N_F(4, F21, 2, a, b, c, d)) << endl;
	//cout << TO_STRING(REVERSE_REPEAT_N_F_ZERO(4, F21, 2, a, b, c, d)) << endl;
	//
	cout << "3..........................................................................." << endl;
#define F3(n, X, Y, Z) COMB(COMB(Y, Z), UDRL_M(COMB(X, n)))
#define F31(n, X, Y, Z) COMB(COMB(COMB(X, Y), Z), n)
#define F32(n, X, Y, Z) COMB(Z, UDRL_M(COMB(COMB(X, Y), n)))
	cout << TO_STRING(REPEAT_A_ZERO) << endl;
	cout << TO_STRING(REPEAT_A_ZERO(F3, 2, A, B, a, b, c)) << endl;
	cout << TO_STRING(REPEAT_F_SEP) << endl;
	cout << TO_STRING(REPEAT_F_SEP(F31, 3, SEM_M, a, b, c, d, c, f, g)) << endl;
	cout << TO_STRING(REPEAT_F_A) << endl;
	cout << TO_STRING(REPEAT_F_A(F32, 2, 1, T, a, b, c, d, e)) << endl;
	//cout << TO_STRING(REPEAT_FUNC(F3, 1, EXPAND(CUTARGS_B(ADD(1, 2), EXPAND(CUTARGS_B(1, CUTARGS(2, T, R, a, b))), EXPAND(CUTARGS_B(2, T, R, a, b)))))) << endl;
	//cout << TO_STRING(REPEAT_1(1, 1, 1, F3, 1, 2, RIS, COMMA_M, T, R, a, b)) << endl;
	//cout << TO_STRING(REPEAT_N_F_A_SEP(2, F3, 1, 2, COMMA_M, A, B, a)) << endl;
	//cout << TO_STRING(REPEAT_N_F_A_SEP_ZERO(4, F3, 1, 2, COMMA_M, A, B, a, b, c)) << endl;
	//cout << TO_STRING(REVERSE_REPEAT_N_F_A_SEP(4, F3, 1, 2, COMMA_M, A, B, a, b, c)) << endl;
	//cout << TO_STRING(REVERSE_REPEAT_N_F_A_SEP_ZERO(4, F3, 1, 2, COMMA_M, A, B, a, b, c, d)) << endl;
	//cout << ". . . . . . . ." << endl;
	//cout << TO_STRING(CUTARGS_B(3, a, b, c)) << endl;
//cout << TO_STRING(F3(1, a, b, c)) << endl;
//cout << TO_STRING(F3_FUNC(1, CUTARGS_B(3, a, b, c))) << endl;
//cout << TO_STRING(REPEAT_1(1, 1, 1, F3, 3, RIS, SEM_M, a, b, c)) << endl;
//cout << TO_STRING(REPEAT_N_F_SEP(1, F3, 3, SEM_M, a, b, c)) << endl;
	//cout << TO_STRING(REPEAT_F_SEP(F31, 3, SEM_M, a, b, c, d, e, f, g)) << endl;
	cout << "4..........................................................................." << endl;

#define F4(n, W, X, Y, Z) COMB(Z, UDRL_M(COMB(COMB(W, X), n)))
#define F4(n, W, X, Y, Z) COMB(COMB(Y, Z), UDRL_M(COMB(COMB(W, X), n)))
#define F4(n, W, X, Y, Z) COMB(COMB(Y, Z), UDRL_M(COMB(COMB(W, X), n)))
#define F4(n, W, X, Y, Z) COMB(COMB(Y, Z), UDRL_M(COMB(COMB(W, X), n)))
	//cout << TO_STRING(REPEAT_1(1, 1, 1, F4, 2, 2, RIS, COMMA_M, T, R, a, b)) << endl;
	//cout << TO_STRING(COMMA_M(COMB(REPEAT_, DEC(2))(RIS(1), SWITCH_CASE(LE(1, 1), DEC(1), 1), DEC(2), F4, 2, 2, RIS, sep, SWITCH_CASE_ARGS_N_R(GT(1, 1), 2, ADD(2, 2), T, R, a, b)))) << endl;
	//cout << TO_STRING(COMB(EXPAND_F(F4, 1, EXPAND(CUTARGS_B(ADD(2, 2), EXPAND(CUTARGS_B(2, CUTARGS(2, T, R, a, b))), CUTARGS_B(2, T, R, a, b)))), COMMA_M(COMB(REPEAT_, DEC(2))(RIS(1), SWITCH_CASE(LE(1, 1), DEC(1), 1), DEC(2), F4, 2, 2, RIS, sep, SWITCH_CASE_ARGS_N_R(GT(1, 1), 2, ADD(2, 2), T, R, a, b))))) << endl;
	//cout << TO_STRING(REPEAT_2(1, 1, 2, F4, 2, 2, RIS, COMMA_M, T, R, a, b)) << endl;
	//cout << TO_STRING(REPEAT_2(1, 2, 2, F4, 2, 2, RIS, COMMA_M, T, R, a, b, c, d)) << endl;
	//cout << TO_STRING(REPEAT_N_F_A_SEP(2, F4, 2, 2, COMMA_M, A, B, a, b)) << endl;
	//cout << TO_STRING(REPEAT_N_F_A_SEP_ZERO(4, F4, 2, 2, COMMA_M, A, B, a, b, c)) << endl;
	//cout << TO_STRING(REVERSE_REPEAT_N_F_A_SEP(4, F4, 2, 2, COMMA_M, A, B, a, b, c, d)) << endl;
	//cout << TO_STRING(REVERSE_REPEAT_N_F_A_SEP_ZERO(4, F4, 2, 2, COMMA_M, A, B, a, b, c, d, e, f)) << endl;
	//cout << "..............." << endl;

	//cout << TO_STRING(CUTARGS_C(1, 2, a, b, c, d)) << endl;
	//cout << TO_STRING(CUTARGS_C(1, 3, a, b, c, d)) << endl;
	//cout << TO_STRING(SWITCH_CASE_ARGS_N_R(0, 1, 3, a, b, c, d)) << endl;
	//cout << TO_STRING(SWITCH_CASE_ARGS_N_R(1, 1, 3, a, b, c, d)) << endl;
	//cout << "..............." << endl;

	return 0;
}