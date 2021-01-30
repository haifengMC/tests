#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <initializer_list>

using namespace std;
mutex m;

struct AData
{
	vector<int> v = { 1, 2, 3 };
	AData& operator=(initializer_list<int> il)
	{
		int id = 0;
		for (int i : il)
			v[id] = i;

		return *this;
	}

};

ostream& operator<<(ostream& os, const AData& data)
{
	//for (auto i : data.v)
	//	os << i << " ";
	for (size_t i = 0; i < data.v.size(); ++i)
		os << data.v[i] << " ";

	return os;
}

struct AItem
{
	AData& data;
	//mutex m;

	AItem(AData& data) : data(data) {}

	void pData(int i)
	{
		cout << data << endl;
		{
			lock_guard<mutex> lk(m);
			data = { i + 10, i + 20, i + 30 };
		}
		cout << data << endl;
	}
};

struct A
{
	mutex m;
	AData data;
	vector<AItem> items;

	void pData(size_t i)
	{
		//lock_guard<mutex> lk(m);

		size_t size = items.size();
		if (i >= size)
			items.resize(i + 1, data);

		items[i].pData(i);


	}
} a;

void f(int i)
{
	a.pData(i);
}

int main()
{
	vector<thread> v;
	for (int i = 0; i < 3; ++i)
		v.emplace_back(f, i);

	for (auto& t : v)
		t.join();

	return true;
}