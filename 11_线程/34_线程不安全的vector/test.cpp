#include "global.h"
#include "hTest.h"
#include "hTool.h"

#include "hRWLock.h"
#include "hContainer.h"
#include "test.h"

void pSize1(const char* name, vector<int>& v, size_t n)
{
	while (n--)
	{
		v.push_back(1);
		cout << name << v.size() << "/" << v.capacity() << " ";
	}

	cout << endl;
}

void pSize2(const char* name, vector<int>& v, size_t n)
{
	cout << "[" << name << "]" << endl;
	while (n--)
	{
		size_t n = v.size();
		v.resize((n / 10 + 1) * 10);
		cout << v.size() << "/" << v.capacity() << " ";
	}

	cout << endl;
}

ostream& operator<<(ostream& os, const D& d)
{
	return os << d.id << ":" << d.name;
}

hRWLock rwLk;
void readFunc(int i)
{

	COUT_LOCK("read lock...:" << rwLk.rdCnt << " " << rwLk.wtCnt << " " << rwLk.writing);
	rwLk.readLock();
	COUT_LOCK("read........:" << rwLk.rdCnt << " " << rwLk.wtCnt << " " << rwLk.writing);
	rwLk.readUnlock();
	COUT_LOCK("read unlock.:" << rwLk.rdCnt << " " << rwLk.wtCnt << " " << rwLk.writing);
}

void writeFunc(int i)
{

	COUT_LOCK("write lock...:" << rwLk.rdCnt << " " << rwLk.wtCnt << " " << rwLk.writing);
	rwLk.writeLock();
	//std::this_thread::sleep_for(chrono::microseconds(20));
	COUT_LOCK("write........:" << rwLk.rdCnt << " " << rwLk.wtCnt << " " << rwLk.writing);
	rwLk.writeUnlock();
	COUT_LOCK("write unlock.:" << rwLk.rdCnt << " " << rwLk.wtCnt << " " << rwLk.writing);

}

AData1& AData1::operator=(initializer_list<int> il)
{
	int id = 0;
	lk.writeLock();
	for (int i : il)
		v[id++] = i;
	lk.writeUnlock();

	return *this;
}

void AMgr1::pData(size_t i)
{
	size_t size = items.size();
	if (i >= size)
		items.emplaceBack();

	items[i].pData(i);
}

ostream& operator<<(ostream& os, const AData1& data)
{
	//for (auto i : data.v)
	//	os << i << " ";
	//
	size_t size = data.v.size();

	for (size_t i = 0; i < size; ++i)
		os << data.v[i] << " ";

	return os;
}

void AItem1::pData(int i)
{
	COUT_LOCK(*AMgr1::data);

	//AMgr::data.
	*AMgr1::data = { i + 10, i + 20, i + 30 };
	//AMgr::data.

	COUT_LOCK(*AMgr1::data);
}

AData1* AMgr1::data = new AData1;

void f1(AMgr1* a, int i)
{
	a->pData(i);
}

AData2& AData2::operator=(initializer_list<int> il)
{
	int id = 0;
	for (int i : il)
		v[id++] = i;

	return *this;
}

ostream& operator<<(ostream& os, const AData2& data)
{
	//for (auto i : data.v)
	//	os << i << " ";
	for (size_t i = 0; i < data.v.size(); ++i)
		os << data.v[i] << " ";

	return os;
}

void AItem2::pData(int i)
{
	//Ò°Ö¸Õë
	//cout << data << endl;
	//data = { i + 10, i + 20, i + 30 };
	//cout << data << endl;
}

void AMgr2::pData(size_t i)
{	
	//lock_guard<mutex> lk(m);
	//size_t size = items.size();
	//if (i >= size)
	//	items.emplaceBack(data);
	//	//items.resize(i + 1, data, m);
	//
	//items[i].pData(i);
}

void f2(AMgr2* a, int i)
{
	a->pData(i);
}

