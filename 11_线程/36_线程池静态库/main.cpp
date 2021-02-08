#include "global.h"
#include "hThread.h"
#include "hThread/hThreadPoolMgr.h"

using namespace std;
using namespace hThread;

struct Test1TaskNode : public hThread::TaskNode
{
	bool onProc()
	{
		COUT_LK(_id << " 任务节点处理onProc()...");
		std::this_thread::sleep_for(1s);
		return true;
	}
};

int main()
{
	{
		PTask t1 = new Task(50, 2, TaskAttrTypeBit::Loop);
		t1->initNodeData(new NodeData());
		t1->addNode(new Test1TaskNode());
		t1->addNode(new Test1TaskNode());
		sThrdPool.commitTasks(t1);
	}
	this_thread::sleep_for(1s);
	sThrdPool.run();
	this_thread::sleep_for(3s);

	ostringstream os;
	Debug(os, sThrdPool);
	COUT_LK(os.str());

	sThrdPool.stop();
	Debug_PtrMap(cout);
	sThrdPoolFin;
	Debug_PtrMap(cout);

	return 0;
}