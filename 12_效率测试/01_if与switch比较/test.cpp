
#include "global.h"
#include "hSingleton.h"
#include "hTest.h"
#include "hTool.h"
#include "test.h"

using namespace std;
TEST_INIT(Tst, testAll)

void printIf(const int& i)
{
	if (i == 0)
		cout << 0 << endl;
	else if (i == 1)
		cout << 1 << endl;
	else if (i == 2)
		cout << 2 << endl;
	else if (i == 3)
		cout << 3 << endl;
	else
		cout << -1 << endl;
}

TEST(Tst, Tst1)
{
	printIf(0);
	printIf(1);
	printIf(2);
	printIf(3);
	printIf(4);
}

void printSwitch(const int& i)
{
	switch (i)
	{
	case 0:
		cout << 0 << endl;
		break;
	case 1:
		cout << 1 << endl;
		break;
	case 2:
		cout << 2 << endl;
		break;
	case 3:
		cout << 3 << endl;
		break;
	default:
		cout << -1 << endl;
		break;
	}
}

TEST(Tst, Tst2)
{
	printSwitch(0);
	printSwitch(1);
	printSwitch(2);
	printSwitch(3);
	printSwitch(4);
}