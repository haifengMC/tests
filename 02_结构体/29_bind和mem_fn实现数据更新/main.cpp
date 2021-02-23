#include <iostream>
#include <list>
#include <map>
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
	map<size_t, Data*> _dataMap;
	void showData();
	template <class ... Args >
	void updata(size_t id, Args ... args);
	void exec() { for (auto fn : _updateList) fn(); }
};

int main()
{
	Update up;
	up._dataMap.insert(make_pair(1, new DataA));
	up._dataMap.insert(make_pair(2, new DataB));
	up.showData();

	up.updata(1, 1, 2);
	up.updata(2, "hello");

	up.exec();
	up.showData();

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

void Update::showData()
{
	for (auto data : _dataMap)
		data.second->showData(cout) << endl;
}

template <class ... Args >
void Update::updata(size_t id, Args ... args)
{
	using namespace std::placeholders;
	auto memFn = bind(mem_fn(&Data::f), _1, 0, args...);
	auto bindFn = [&](decltype(memFn) memFn)
	{
		auto it = _dataMap.find(id);
		if (it == _dataMap.end())
			return;

		memFn(it->second);
	};
	auto fn = bind(bindFn, memFn);
	fn();
	//_updateList.push_back(function<void()>(fn));
}