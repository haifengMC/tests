#include "global.h"
#include "hTest.h"
#include "hTool.h"

#include "hRWLock.h"
#include "hContainer.h"
#include "test.h"
using namespace std;

TEST_INIT()
TEST(vector内存分配变化1)
{
	vector<int> v1;
	pSize1("v1", v1, 10);
	vector<int> v2;
	pSize1("v2", v2, 20);
}

TEST(vector内存分配变化2)
{
	vector<int> v1;
	pSize2("v1", v1, 10);
	vector<int> v2;
	pSize2("v2", v2, 20);
}

TEST(realloc分配内存)
{
	void* p1 = malloc(10);
	cout << "<p1>" << p1 << endl;
	void* p2 = realloc(p1, 100);
	cout << "<p1>" << p1 << "<p2>" << p2 << endl;
	void* p3 = realloc(p2, 10000000000000000);
	cout << "<p1>" << p1 << "<p2>" << p2 << "<p3>" << p3 << endl;
	free(p2);
}

TEST(内存分配器随机访问)
{
	hAlloc<int> a;
	a.allocate(10);
	for (size_t i = 0; i < a.size(); ++i)
		cout << a[i] << endl;
	a.deallocate();
}

TEST(类类型pushBack测试)
{
	A a;
	hVector<A> vA;
	vA.pushBack(a);
	vA.pushBack(move(a));
	vA.pushBack(A());

	B b;
	hVector<B> vB;
	vB.pushBack(b);
	vB.pushBack(move(b));
	vB.pushBack(B());

	C c;
	hVector<C> vC;
	//vC.pushBack(c);
	vC.pushBack(move(c));
	vC.pushBack(C());
}

TEST(pushBack测试)
{
	hVector<int> v;
	for (int i = 0; i < 20; ++i)
	{
		v.pushBack(i);
		cout << v[i] << ":" << v.size() << "/" << v.capacity() << " ";
	}

	cout << endl;
}

TEST(emplaceBack测试)
{
	hVector<int> v;
	for (int i = 0; i < 20; ++i)
	{
		v.emplaceBack(i);
		cout << v[i] << ":" << v.size() << "/" << v.capacity() << " ";
	}

	cout << endl;
}

TEST(类类型emplaceBack测试)
{
	hVector<D> v;
	cout << v.emplaceBack(1, "hong") << endl;
	cout << v.emplaceBack(2, "ming") << endl;
	cout << v.emplaceBack(3, "lucy") << endl;
	cout << v.emplaceBack(4, "peter") << endl;
	cout << v.emplaceBack(5, "hua") << endl;
	
	for (int i = 0; i < v.size(); ++i)
		cout << v[i] << " ";
	cout << endl;
}

TEST(resize测试)
{
	hVector<int> v1 = { 1,2,3,4,5,6,7,8,9,10 };
	cout << v1.size() << " " << v1.capacity() << endl;
	v1.resize(2);
	cout << v1.size() << " " << v1.capacity() << endl;
	v1.resize(20);
	cout << v1.size() << " " << v1.capacity() << endl;
	v1.clear();
	cout << v1.size() << " " << v1.capacity() << endl;

	vector<int> v2 = { 1,2,3,4,5,6,7,8,9,10 };
	cout << v2.size() << " " << v2.capacity() << endl;
	v2.resize(2);
	cout << v2.size() << " " << v2.capacity() << endl;
	v2.resize(20);
	cout << v2.size() << " " << v2.capacity() << endl;
	v2.clear();
	cout << v2.size() << " " << v2.capacity() << endl;
}

TEST(迭代器测试)
{
	//vector<int> v = {1,2,3};
	//
	//auto beg = v.begin();
	//cout << *beg << endl;
	//v.push_back(4);
	//++beg;
	//cout << *beg << endl;
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

TEST(读写锁测试)
{
	vector<thread> rwVec;
	for (int i = 1; i <= 10; ++i)
		rwVec.emplace_back(readFunc, i);
	vector<thread> wtVec;
	for (int i = 1; i <= 10; ++i)
		wtVec.emplace_back(writeFunc, i);

	for (thread& thd : rwVec)
		thd.join();
	for (thread& thd : wtVec)
		thd.join();
}

TEST(hVector管理含互斥锁类类型1)
{
	AMgr1 a;
	hVector<thread> v;
	for (int i = 0; i < 9; ++i)
		v.emplaceBack(f1, &a, i);
	//std::this_thread::sleep_for(chrono::seconds(20));
	for (int i = 0; i < v.size(); ++i)
		v[i].join();
	//for (auto& t : v)
	//	t.join();

}

TEST(hVector管理含互斥锁类类型2)
{
	AMgr2 a;
	hVector<thread> v;
	for (int i = 0; i < 9; ++i)
		v.emplaceBack(f2, &a, i);
	//std::this_thread::sleep_for(chrono::seconds(20));
	for (int i = 0; i < v.size(); ++i)
		v[i].join();
	//for (auto& t : v)
	//	t.join();

}


TEST_MAIN()
