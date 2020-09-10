#include "global.h"
#include "hTest.h"

using namespace std;

TEST_INIT(Tst, testAll)


class A : public Singleton<A>
{
public:
	int add(int a, int b) { return a + b; }
	int sub(int a, int b) { return a - b; }
	int mul(int a, int b) { return a * b; }
	int div(int a, int b) { return a / b; }
};

template <class Func, class ... Args>
void funcA(Func func, Args ... args)
{
	cout << (A::getMe().*func)(args...) << endl;
}

//#define FUNCA(type, func, ...)\
//	funcA<type, type::*func>(&type::func, ##__VA_ARGS__)
#define FUNCA(type, func, ...)\
	cout << type::getMe().func(##__VA_ARGS__) << endl

TEST(Tst, Tst1)
{
	FUNCA(A, add, 1, 2);
	
	//auto pFunc = &A::add;
	//cout << (A::getMe().*pFunc)(1, 2) << endl;
}

class B
{
public:
	B(int i) { j = i; p = &B::C; };
	void C() { printf("C %d\n", j); };
	void (B::* p)();
	int j;
};

TEST(Tst, Tst2)
{
	B a(1);
	B b(2);
	(b.*a.p)();//thisÖ¸ÕëÎªb
}

TEST_MAIN(testAll);