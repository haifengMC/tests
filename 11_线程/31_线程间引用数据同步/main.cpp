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
		std::lock_guard<std::mutex> lk(m);
		int id = 0;
		for (auto i : il)
			v[id++] = i;

		return *this;
	}

	size_t size() const
	{
		std::lock_guard<std::mutex> lk(m);
		return v.size();
	}
};

ostream& operator<<(ostream& os, const AData& data)
{
	int n = data.size();
	vector<int> v;
	for (int i = 0; i < n; ++i)
		v.push_back(data.v[i]);
	{
		std::lock_guard<std::mutex> lk(m);
		for (int i = 0; i < n; ++i)
			os << v[i] << " ";
		os << "\n------------\n";
	}

	return os;
}

struct AItem
{
	AData& data;

	AItem(AData& data) : data(data) {}

	void pData(int i)
	{
		cout << data;
		data = { i + 10, i + 20, i + 30 };
		cout << data;
	}
};

struct A
{
	AData data;
	vector<AItem> items;

	void pData(int i)
	{
		for (int j = items.size(); j <= i; ++j)
			items.emplace_back(data);

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