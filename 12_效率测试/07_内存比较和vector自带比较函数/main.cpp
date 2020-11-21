#include "global.h"
#include "hTest.h"

using namespace std;
TEST_INIT()

vector<int> v1(1000000, 1);
vector<int> v2(1000000, 1);

bool ret1 = false;
bool ret2 = false;

TEST(内存比较)
{
	ret1 = !memcmp(v1.data(), v2.data(), sizeof(int) * v1.size());
}


TEST(vector自带函数比较)
{
	ret2 = v1 == v2;
}

TEST(比较结果)
{
	cout << ret1 << " " << ret2 << endl;
}

TEST_MAIN()