#include <iostream>

using namespace std;

#define PI 3.14
#define MUL_PI(n) n * PI
#define TWO 2

//�Ժ����������#����##,��ô�ú�������ᱻչ����Ϊ����x���չ��дTO_STRING1
#define TO_STRING(x) TO_STRING1(x)
#define TO_STRING1(x) #x

int main()
{
	cout << MUL_PI(TWO) << endl;
	cout << TO_STRING(hello) << endl;

	return 0;
}