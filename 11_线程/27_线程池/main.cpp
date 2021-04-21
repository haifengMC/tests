#include "global.h"
#include "hSingleton.h"
#include "hTool.h"
#include "hTest.h"
#include "hThread.h"
#include "hPoolMgr.h"
#include "test.h"

TEST_INIT()
{
	addAttr(TestAttrType::Tail, 1);
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
	hPoolMgr& pool = shPoolMgr;
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

TEST(����ָ�����3)
{
	{
		hTool::hAutoPtr<Test3A> pA(new Test3A);
		Test3P(1);
		{
			hTool::hAutoPtr<Test3B> pB(new Test3B);
			Test3P(2);
			{
				hTool::hAutoPtr<Test3C> pC(new Test3C);
				Test3P(3);
				pA->addPtr(pC);
				Test3P(4);
				pB->addPtr(pA);
				//TestP(5);
				//pC->addPtr(pB);
				Test3P(6);
			}
			Test3P(7);
		}
		Test3P(8);
	}
	Test3P(9);
}

TEST(����ָ�����4)
{
	{
		hTool::hAutoPtr<Test4A> pA(new Test4A);
		Test4P(1);
		{
			hTool::hAutoPtr<Test4B> pB(new Test4B);
			Test4P(2);
			pA->addPtr(pB.dynamic());
			Test4P(5);
			pB->addPtr(pA.dynamic());
			Test4P(8);
		}
		Test4P(9);
	}
	Test4P(10);
}

TEST(����ָ�����5)
{
	Test5Base* pTBase = new Test5;
	Test5* pT1 = hTool::hDynamicCast<Test5*>(pTBase);
	Test5* pT2 = dynamic_cast<Test5*>(pTBase);
	cout << pT1 << " " << pT2 << endl;
	DEL(pTBase);
}

TEST(�����������)
{
	hTaskBase t(50, 2, TaskAttrTypeBit::Loop);
	Debug(cout, t) << endl;
	t.initNodeData();
	Debug(cout, t) << endl;
	t.addNode(new hNode);
	t.addNode(new hNode);
	Debug(cout, t) << endl;
}

TEST(����������Զ������ݺͽڵ�)
{
	hTaskBase t(50, 2, TaskAttrType::Loop);
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

TEST(id������debug)
{
	hTool::hUniqueIdGen<size_t, hTaskBase> _tasksIdGen(50, 1, 100);
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

TEST(�ύ���񵽹�����)
{
	TaskMgrCfgItem base;
	hTaskMgrBase tM;
	tM.init(base);
	Debug(cout, tM) << endl;
	PhTask t1 = new hTaskBase(50, 2, TaskAttrType::Loop);
	t1->initNodeData(new TestNodeData("test data"));
	t1->addNode(new TestTaskNode("test node1"));
	t1->addNode(new TestTaskNode("test node2"));
	tM.commitTasks(t1);
	Debug(cout, tM) << endl;	
	PhTask t2[2] = 
	{ 
		new hTaskBase(50, 2, TaskAttrTypeBit::Loop), 
		new hTaskBase(50, 2, TaskAttrTypeBit::Loop)
	};
	t2[0]->initNodeData();
	t2[0]->addNode(new hNode);
	t2[0]->addNode(new hNode);
	t2[1]->initNodeData(new TestNodeData("test data"));
	t2[1]->addNode(new TestTaskNode("test node1"));
	t2[1]->addNode(new TestTaskNode("test node2"));
	tM.commitTasks(t2);
	Debug(cout, tM) << endl;
}

TEST(�ύ�����̳߳���־)
{
	PhTask t1 = new hTaskBase(50, 2, TaskAttrType::Loop);
	t1->initNodeData(new TestNodeData("test data"));
	t1->addNode(new TestTaskNode("test node1"));
	t1->addNode(new TestTaskNode("test node2"));
	shPool.commitTasks(t1);
	Debug(cout, shPool) << endl;
	PhTask t2[2] =
	{
		new hTaskBase(50, 2, TaskAttrTypeBit::Loop),
		new hTaskBase(50, 2, TaskAttrTypeBit::Loop)
	};
	t2[0]->initNodeData();
	t2[0]->addNode(new hNode);
	t2[0]->addNode(new hNode);
	t2[1]->initNodeData(new TestNodeData("test data"));
	t2[1]->addNode(new TestTaskNode("test node1"));
	t2[1]->addNode(new TestTaskNode("test node2"));
	shPool.commitTasks(t2, TaskMgrPriority::Higher);
	Debug(cout, shPool) << endl;
}

TEST(�̳߳�����5��)
{
	{
		//PhTask t1 = new hTaskBase(50, 2, TaskAttrTypeBit::Loop);
		//t1->initNodeData(new NodeData());
		//t1->addNode(new Test1TaskNode());
		//t1->addNode(new Test1TaskNode());
		//shPool.commitTasks(t1);
		PhTask t2 = new hTaskBase(50, 2, TaskAttrTypeBit::Loop);
		t2->initNodeData(new hUserData());
		t2->addNode(new Test1TaskNode());
		t2->addNode(new Test1TaskNode());
		shPool.commitTasks(t2);
	}
	//this_thread::sleep_for(1s);
	shPool.run();
	system("pause");
	//this_thread::sleep_for(10s);
	//{
	//	string is;
	//	PhTask t;
	//	t.bind(new Test2Task);
	//	shPool.commitTasks(t);
	//	while (1)
	//	{
	//
	//		cin >> is;
	//		if (is == "quit")
	//			break;
	//		t->updateTaskData(0, is.c_str());
	//	}
	//}

	ostringstream os;
	Debug(os, shPool);
	COUT_LK(os.str());

	shPool.stop();
	Debug_PtrMap(cout);
	hTool::hAutoPtr<hTool::hWeakPtrBase>::debugMap(cout);
	shPoolFin;
	Debug_PtrMap(cout);
	hTool::hAutoPtr<hTool::hWeakPtrBase>::debugMap(cout);
}

TEST_MAIN()