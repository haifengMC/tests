#include "global.h"
#include "hTest.h"

using namespace std;
TEST_INIT()

vector<int> v1(1000000, 1);
vector<int> v2(1000000, 1);

bool ret1 = false;
bool ret2 = false;

TEST(�ڴ�Ƚ�)
{
	ret1 = !memcmp(v1.data(), v2.data(), sizeof(int) * v1.size());
}


TEST(vector�Դ������Ƚ�)
{
	ret2 = v1 == v2;
}

TEST(�ȽϽ��)
{
	cout << ret1 << " " << ret2 << endl;
}

TEST_MAIN()