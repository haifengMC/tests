#include <iostream>

using namespace std;


#define TO_STRING(X) TO_STRING1(X)
#define TO_STRING1(X) #X

#define COMB(X, Y) COMB1(X, Y)
#define COMB1(X, Y) X##Y

#define COMMA_M(X) ,X


#define DEC_1 0
#define DEC_2 1
#define DEC_3 2
#define DEC(n) COMB(DEC_, n)

#define REPEAT_1(n, f, e) f(n, e)
#define REPEAT_2(n, f, e) COMB(COMB(REPEAT_, DEC(n))(DEC(n), f, e), COMMA(f(n, e)))
#define REPEAT_3(n, f, e) COMB(COMB(REPEAT_, DEC(n))(DEC(n), f, e), COMMA(f(n, e)))

#define TEST1(n, x) x 
#define TEST2(n, x) COMB(x, n)

#define ARGS(type, n) 

int main()
{
	cout << TO_STRING(COMB(1, 2)) << endl;
	cout << TO_STRING(DEC(3)) << endl;
	cout << TO_STRING(REPEAT_2(2, TEST1, X)) << endl;
	cout << TO_STRING(REPEAT_3(3, TEST2, X)) << endl;


	return 0;
}