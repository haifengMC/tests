#include <iostream>
#include <list>
#include <functional>
#include <stdarg.h>

using namespace std;

struct Data
{
	
	virtual ~Data() {}
	virtual void f(int opt, ...) { cout << "Data::f()" << endl; }
	virtual ostream& showData(ostream& os) { return os; }
	
};
struct DataA : public Data 
{
	int _a = 0, _b = 0;
	void f(int opt, ...);
	ostream& showData(ostream& os) { return os << "DataA:" << _a << " " << _b; }
};

struct DataB : public Data 
{ 
	string _s;
	void f(int opt, ...);
	ostream& showData(ostream& os) { return os << "DataB:" << _s; }
};

struct Update
{
	list<function<void()>> _updateList;
	template <class ... Args >
	void updata(Data* pData, Args ... args);
	void exec() { for (auto fn : _updateList) fn(); }
};

int main()
{
	Update up;

	Data* pA = new DataA;
	Data* pB = new DataB;
	pA->showData(cout) << endl;
	pB->showData(cout) << endl;

	up.updata(pA, 1, 2);
	up.updata(pB, "hello");

	up.exec();
	pA->showData(cout) << endl;
	pB->showData(cout) << endl;

	delete pA;
	delete pB;
#if 0
	auto fn = mem_fn(&Data::f);

	updateList.push_back(function<void()>(bind(fn, pA)));
	updateList.push_back(function<void()>(bind(fn, pB)));

	for (auto fn : updateList)
		fn();
#endif

	return 0;
}

void DataA::f(int opt, ...)
{
	cout << "DataA::f()" << endl;
	int a = 0, b = 0;
	va_list arg_ptr;
	va_start(arg_ptr, opt);
	a = va_arg(arg_ptr, decltype(a));
	b = va_arg(arg_ptr, decltype(b));
	va_end(arg_ptr);
	_a = a;
	_b = b;
}

void DataB::f(int opt, ...)
{
	cout << "DataB::f()" << endl;
	const char* s;
	va_list arg_ptr;
	va_start(arg_ptr, opt);
	s = va_arg(arg_ptr, decltype(s));
	va_end(arg_ptr);
	_s = s;
}

template <class ... Args >
void Update::updata(Data* pData, Args ... args)
{
	auto fn = mem_fn(&Data::f);
	_updateList.push_back(function<void()>(bind(fn, pData, 0, args...)));
}