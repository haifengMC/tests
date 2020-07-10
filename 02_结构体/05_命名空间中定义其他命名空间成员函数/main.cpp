#include <iostream>

using namespace std;

namespace A
{
	void func() { cout << "A" << endl; }
}
namespace B
{
	namespace A
	{
		void func() { cout << "B A" << endl; }
	}
	void printFunc()
	{
		A::func();
		::A::func();
	}
}

int main()
{
	B::printFunc();

	return 0;
}