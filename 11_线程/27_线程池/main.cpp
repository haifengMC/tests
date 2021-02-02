#include "global.h"
#include "hSingleton.h"
#include "hTool.h"
#include "hTest.h"
#include "hThread.h"
#include "hThreadPoolMgr.h"
#include "test.h"

TEST_INIT()
{
	addAttr(TestAttrType::Tail, 1);
	Debug(std::cout, *this) << std::endl;
}

using namespace std;
using namespace hThread;

TEST(任务枚举类型测试)
{
	TaskStatType e;
	cout << e.getName() << " " << e << endl;
	e = TaskStatType::Wait;
	cout << e.getName() << " " << e << endl;
}

TEST(线程池配置加载)
{
	ThreadPoolMgr& pool = sThrdPoolMgr;
}

TEST(读写锁测试)
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

TEST(智能指针测试1)
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

TEST(智能指针测试2)
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

TEST(创建任务测试)
{
	Task t(50, 2, TaskAttrTypeBit::Loop);
	Debug(cout, t) << endl;
	t.initNodeData();
	Debug(cout, t) << endl;
	t.addNode(new TaskNode);
	t.addNode(new TaskNode);
	Debug(cout, t) << endl;
}

TEST(向任务添加自定义数据和节点)
{
	Task t(50, 2, TaskAttrType::Loop);
	t.initNodeData(new TestNodeData("test data"));
	t.addNode(new TestTaskNode("test node1"));
	t.addNode(new TestTaskNode("test node2"));
	Debug(cout, t) << endl;
}

TEST(按权重随机生成)
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

TEST(id生成器debug)
{
	hTool::hUniqueIdGen<size_t, Task> _tasksIdGen(50, 1, 100);
	Debug(cout, _tasksIdGen) << endl;
	InsertTask(t1);
	InsertTask(t2);
	Debug(cout, _tasksIdGen) << endl;
	_tasksIdGen.erase(t1);
	Debug(cout, _tasksIdGen) << endl;
	InsertTask(t3);
	Debug(cout, _tasksIdGen) << endl;
	InsertTask(t4);
	Debug(cout, _tasksIdGen) << endl;
}

TEST(提交任务到管理器)
{
	TaskMgrCfgItem base;
	TaskMgr tM(base);
	Debug(cout, tM) << endl;
	PTask t1 = new Task(50, 2, TaskAttrType::Loop);
	t1->initNodeData(new TestNodeData("test data"));
	t1->addNode(new TestTaskNode("test node1"));
	t1->addNode(new TestTaskNode("test node2"));
	tM.commitTasks(t1);
	Debug(cout, tM) << endl;	
	PTask t2[2] = 
	{ 
		new Task(50, 2, TaskAttrTypeBit::Loop), 
		new Task(50, 2, TaskAttrTypeBit::Loop)
	};
	t2[0]->initNodeData();
	t2[0]->addNode(new TaskNode);
	t2[0]->addNode(new TaskNode);
	t2[1]->initNodeData(new TestNodeData("test data"));
	t2[1]->addNode(new TestTaskNode("test node1"));
	t2[1]->addNode(new TestTaskNode("test node2"));
	tM.commitTasks(t2);
	Debug(cout, tM) << endl;
}

TEST(提交任务到线程池日志)
{
	PTask t1 = new Task(50, 2, TaskAttrType::Loop);
	t1->initNodeData(new TestNodeData("test data"));
	t1->addNode(new TestTaskNode("test node1"));
	t1->addNode(new TestTaskNode("test node2"));
	sThrdPool.commitTasks(t1);
	Debug(cout, sThrdPool) << endl;
	PTask t2[2] =
	{
		new Task(50, 2, TaskAttrTypeBit::Loop),
		new Task(50, 2, TaskAttrTypeBit::Loop)
	};
	t2[0]->initNodeData();
	t2[0]->addNode(new TaskNode);
	t2[0]->addNode(new TaskNode);
	t2[1]->initNodeData(new TestNodeData("test data"));
	t2[1]->addNode(new TestTaskNode("test node1"));
	t2[1]->addNode(new TestTaskNode("test node2"));
	sThrdPool.commitTasks(t2, TaskMgrPriority::Higher);
	Debug(cout, sThrdPool) << endl;
}

TEST(线程池运行5秒)
{
	PTask t1 = new Task(50, 2, TaskAttrType::Loop);
	t1->initNodeData(new TestNodeData("test data"));
	t1->addNode(new TestTaskNode("test node1"));
	t1->addNode(new TestTaskNode("test node2"));
	sThrdPool.commitTasks(t1);
	this_thread::sleep_for(1s);
	sThrdPool.run();
	this_thread::sleep_for(1s);
	Debug(cout, sThrdPool) << endl;
	this_thread::sleep_for(4s);
	sThrdPool.stop();
}

TEST_MAIN()