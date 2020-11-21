#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <initializer_list>

using namespace std;

struct AData
{
	vector<int> v = { 1, 2, 3 };

	AData& operator=(initializer_list<int> il)
	{
		v.clear();
		for (int i : il)
			v.push_back(i);

		return *this;
	}

};

ostream& operator<<(ostream& os, const AData& data)
{
	for (auto i : data.v)
		os << i << " ";

	return os;
}

struct AItem
{
	AData& data;
	mutex m;

	AItem(AData& data) : data(data) {}

	void pData(int i)
	{
		cout << data << endl;
		data = { i + 10, i + 20, i + 30 };
		cout << data << endl;
	}
};

struct A
{
	mutex m;
	AData data;
	vector<AItem> items;

	void pData(int i)
	{
		lock_guard<mutex> lk(m);

		size_t size = items.size();
		if (i < size)
		{
			items[i].pData(i);
			return;
		}

		for (size_t j = size; i <= i; ++j)
		{
			items.reserve(i + 1);
			//AItem item(data);
			//items.insert(items.end(), move(AItem(data)));
			//items.emplace_back(data);
		}

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