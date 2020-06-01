#include "global.h"
#include "uValue.h"
#include "vcommon.h"

using namespace std;

class A {};

//ENUM(EnumTest, EnumTest_test1, "EnumTest::test1", EnumTest_test2, "EnumTest::test2", EnumTest_test3, "EnumTest::test3")

int main()
{
#if 0
	//cout << TO_STRING(REPEAT_F_A_SEP(ENUM_CASE_F, 2, 1, SEM_M, EnumTest, test1, "EnumTest::test1")) << endl;
	//cout << TO_STRING(ENUM(EnumTest, EnumTest_test1, "EnumTest::test1", EnumTest_test2, "EnumTest::test2", EnumTest_test3, "EnumTest::test3")) << endl;
	EnumTest a = EnumTest::EnumTest_test1;
	EnumTest b = EnumTest::EnumTest_test2;
	EnumTest c = EnumTest::EnumTest_test3;
	
	cout << a << " " << b << " " << c << endl;
#endif


	//cout << TO_STRING(OPERATOR(uValueType_Int, int, v.i)) << endl;
	//cout << TO_STRING(EXPAND(REPEAT_F_SEP(OPERATOR_CASE_F, 3, SEM_M, uValueType_Int, int, v.i,
	//	uValueType_Uint, unsigned int, v.u, ));) << endl;
	
	uValue u;
	int i = 1;
	unsigned int ui = 2;
	long l = 3;
	unsigned long ul = 4;
	float f = 5.5f;
	double d = 6.6;
	std::string s = "hello";
	A a;
	cout << u.getType() << "[" << u << "]" << endl;
	u = i;
	cout << u.getType() << "[" << u << "]" << endl;
	u = ui;
	cout << u.getType() << "[" << u << "]" << endl;
	u = l;
	cout << u.getType() << "[" << u << "]" << endl;
	u = ul;
	cout << u.getType() << "[" << u << "]" << endl;
	u = f;
	cout << u.getType() << "[" << u << "]" << endl;
	u = d;
	cout << u.getType() << "[" << u << "]" << endl;
	u = s;
	cout << u.getType() << "[" << u << "]" << endl;
	u = "world";
	cout << u.getType() << "[" << u << "]" << endl;
	u = a;
	cout << u.getType() << "[" << u << "]" << endl;
	
	

	return 0;
}
