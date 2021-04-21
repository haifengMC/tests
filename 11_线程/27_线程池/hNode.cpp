#include "global.h"
#include "hThread.h"
#include "hPoolMgr.h"

namespace hThread
{
	void hNode::init(size_t id, PhUserDt data)
	{
		_id = id;
		_data = data;
	}

	bool hNode::handle_initProc()
	{
		return initProc();
	}

	bool hNode::handle_preProc()
	{
		bool ret = true;
		_data->readLk([&]() { ret = preProc(); });
		return ret;
	}

	bool hNode::handle_waitProc(PWhTask pTsk, hNodeListIt nodeIt)
	{
		bool ret = true;
		_data->writeLk([&]()
			{
				ret = pTsk->canProc(nodeIt);
				if (!ret)
				{
					COUT_LK(" task_" << pTsk->getId() <<
						"任务等待前置节点完成," <<
						"_curNodeIt:" << (*pTsk->getCurNodeIt())->getId() <<
						"_nodeIt:" << (*nodeIt)->getId() << "...");
				}
			});
		return ret;
	}

	bool hNode::handle_onProc()
	{
		bool ret = true;
		_data->writeLk([&]() { ret = onProc(); });
		return ret;
	}

	hNodeListIt hNode::handle_succProc(PWhTask pTsk, hWorkMemListIt memIt)
	{
		finalProc();
		hNodeListIt it;
		_data->writeLk([&]()
			{
				pTsk->finishCurNode(memIt);
				it = pTsk->getNextNode();
			});

		COUT_LK("WorkMem_" << (*memIt)->getId() 
			<< " 任务task_" << pTsk->getIndex() 
			<< "节点" << getId() << "处理完成...");

		return it;
	}

	bool hNode::handle_failProc()
	{
		return finalProc();
	}

}