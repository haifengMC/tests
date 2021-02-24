#include "global.h"
#include "hThread.h"
#include "hThread/hThreadPoolMgr.h"
#include "test.h"

using namespace std;
using namespace hThread;

int main()
{
	{
		/*
				PTask t1 = new Task(50, 2, TaskAttrTypeBit::Loop);
				t1->initNodeData(new NodeData());
				t1->addNode(new Test1TaskNode());
				t1->addNode(new Test1TaskNode());
				sThrdPool.commitTasks(t1);
				PTask t2 = new Task(50, 2);
				t2->initNodeData(new NodeData());
				t2->addNode(new Test1TaskNode());
				t2->addNode(new Test1TaskNode());
				sThrdPool.commitTasks(t2);
		*/
	}
	//this_thread::sleep_for(1s);
	sThrdPool.run();
	this_thread::sleep_for(1s);
	{
		string is;
		PTask t;
		t.bind(new Test2Task);
		sThrdPool.commitTasks(t);
		while (1)
		{

			cin >> is;
			if (is == "quit")
				break;
			t->updateTaskData(0, is.c_str());
		}
	}

	ostringstream os;
	Debug(os, sThrdPool);
	COUT_LK(os.str());

	sThrdPool.stop();
	Debug_PtrMap(cout);
	hTool::hAutoPtr<hTool::hWeakPtrBase>::debugMap(cout);
	sThrdPoolFin;
	Debug_PtrMap(cout);
	hTool::hAutoPtr<hTool::hWeakPtrBase>::debugMap(cout);

	return 0;
}