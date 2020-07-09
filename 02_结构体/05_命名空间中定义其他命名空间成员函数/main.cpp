#include <iostream>

using namespace std;

namespace A
{
	class A1
	{
	public:
		void func();
	};

	class C;
}



namespace B
{

	void ::A::A1::func()
	{
		cout << "B ::A::A1::func" << endl;
	}

	class ::A::C
	{

	};
}




int main()
{


	return 0;
}