#include "global.h"
#include "hThread.h"
#include "hThreadPoolMgr.h"

namespace hThread
{
	TreadPool::TreadPool() : 
		_invalid(sTreadPoolMgr), base(sTreadPoolMgr.getBaseCfg()),
		busyThd(0)
	{
		if (_invalid)
		{//Err
			return;
		}
		init();
	}

	void TreadPool::init()
	{
		for (auto& item : sTreadPoolMgr.getTaskMgrCfg())
			taskMgrs.emplace_back(item.second);
	}

	void TreadPool::final()
	{
	}

	void TreadPool::run()
	{
	}

	void TreadPool::stop()
	{
	}
}