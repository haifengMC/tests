#include "global.h"
#include "hSingleton.h"
#include "hTool.h"
#include "hTest.h"
#include "hThread.h"
#include "hThreadPoolMgr.h"
#include "test.h"

TEST_INIT()
{
	addAttr(TestAttrType::Tail, 3);
	Debug(std::cout, *this) << std::endl;
}

using namespace std;
using namespace hThread;

TEST(����ö�����Ͳ���)
{
	TaskStatType e;
	cout << e.getName() << " " << e << endl;
	e = TaskStatType::Wait;
	cout << e.getName() << " " << e << endl;
}

TEST(�̳߳����ü���)
{
	ThreadPoolMgr& pool = sTreadPoolMgr;
}

TEST(��д������)
{
	int iR = 1001;
	int iW = 1001;

	vector<thread> rwVec;
	for (; iR < 1011; ++iR)
		rwVec.emplace_back(readFunc, iR);
	vector<thread> wtVec;
	for (; iW <= 1011; ++iW)
		wtVec.emplace_back(writeFunc, iW);

	for (thread& thd : rwVec)
		thd.join();
	for (thread& thd : wtVec)
		thd.join();
}

TEST(����ָ�����1)
{
	vector<hTool::hAutoPtr<int>> v;
	cout << "......" << endl;
	v.push_back(new int(1));
	cout << "......" << endl;
	v.push_back(new int(2));
	cout << "......" << endl;
	v.push_back(new int(3));
	cout << "......" << endl;
	for (auto& i : v)
		cout << *i << endl;
}

TEST(����ָ�����2)
{
	list<hTool::hAutoPtr<int>> l;
	cout << "......" << endl;
	l.push_back(new int(1));
	cout << "......" << endl;
	l.push_back(new int(2));
	cout << "......" << endl;
	l.push_back(new int(3));
	cout << "......" << endl;
	for (auto& i : l)
		cout << *i << endl;
}

TEST(�����������)
{
	Task t(50, 2, TaskAttrTypeBit::Loop);
	Debug(cout, t) << endl;
	t.initNodeData();
	Debug(cout, t) << endl;
	t.addNode(new TaskNode);
	t.addNode(new TaskNode);
	Debug(cout, t) << endl;
}

TEST(����������Զ������ݺͽڵ�)
{
	Task t(50, 2, TaskAttrType::Loop);
	t.initNodeData(new TestNodeData("test data"));
	t.addNode(new TestTaskNode("test node1"));
	t.addNode(new TestTaskNode("test node2"));
	Debug(cout, t) << endl;
}

TEST(��Ȩ���������)
{
	hTool::hRWeightMap<size_t> wM =
	{
		hTool::hRWeight<size_t>(100, {1,2,3}),
		hTool::hRWeight<size_t>(200, {4,5,6}),
		hTool::hRWeight<size_t>(300, {7,8,9}),
	};
	Debug(cout, wM) << endl;
	for (size_t i = 0; i < 4; ++i)
	{
		auto tmpWM = wM;
		vector<size_t> v;
		for (size_t j = 0; j < 4; ++j)
		{
			v.clear();
			tmpWM.getRandVal(v, 4);
			for (auto k : v)
				cout << k << " ";
			cout << endl;
			Debug(cout, tmpWM) << endl;
		}
	}
}

TEST(�������������)
{
	TaskMgrCfgItem base;
	TaskMgr tM(base);
	Debug(cout, tM) << endl;

}

TEST(id������debug)
{
	std::map <size_t, Task> _tasks;
	hTool::hUniqueIdGen<size_t, Task> _tasksIdGen(_tasks, 50);
	Debug(cout, _tasksIdGen) << endl;
}

TEST_MAIN()