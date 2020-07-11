#include "global.h"
#include "hThread.h"

namespace hThread
{
	TreadPool::TreadPool() : _invalid(false), busyThd(0), cfgData("hThread.yml")
	{
		if (!cfgData.loadCfg())
		{//Err
			_invalid = true;
			return;
		}
		init();
	}

	void TreadPool::init()
	{
		//for (const TaskMgrCfgItem& item : cfgData.taskMgrCfg)
		//	taskMgrs.emplace_back(item.second);
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