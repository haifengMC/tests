#include <iostream>

using namespace std;

struct BaseA { virtual ~BaseA() {} };
struct BaseB { virtual ~BaseB() {} };
struct Child : public BaseA, public BaseB {};
int main()
{
	BaseA* pA = new Child;
	cout << pA << endl;
	BaseB* pB = dynamic_cast<BaseB*>(pA);
	cout << pB << endl;
	cout << dynamic_cast<BaseA*>(pB) << endl;
	return 0;
}