#include <iostream>

using namespace std;

namespace A
{
	class A1
	{
	public:
		void func();
	};
}



namespace B
{
	void ::A::A1::func()
	{
		cout << "B ::A::A1::func" << endl;
	}
}




int main()
{


	return 0;
}