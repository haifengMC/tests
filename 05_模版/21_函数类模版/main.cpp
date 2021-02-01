#include <iostream>
#include <functional>

using namespace std;

class A
{
	size_t _i = 0;
	function<void()> _func;
public:
	A(size_t i)
	{
		_i = i;
		_func = [&]()
		{
			cout << _i << endl;
		};
	}

	void run() { _func(); }
};

int main()
{
	A a(10);
	a.run();

	return 0;
}