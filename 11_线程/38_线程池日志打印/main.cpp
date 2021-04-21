#include "global.h"
#include "hTool.h"

class A
{
	DefLog_Init();
	int a = 10;
};
DefLog(A, a);

class B : public A
{
	DefLog_Init();
	int b = 20;
};
DefLog(B, b, a);

int main()
{
	A a;
	Debug(std::cout, a) << std::endl;
	B b;
	Debug(std::cout, b) << std::endl;

	return 0;
}