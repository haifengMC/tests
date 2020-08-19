#include "global.h"
#include "hTest.h"

using namespace std;
TEST_INIT(Tst, testAll)

vector<int> v1(100000, 1);

TEST(Tst, Tst1)
{
	vector<int> v;
	v.swap(v1);
}

vector<int> v2(100000, 1);

TEST(Tst, Tst2)
{
	vector<int> v;
	v = v2;
}

int main()
{
	testAll();
	return 0;
}
