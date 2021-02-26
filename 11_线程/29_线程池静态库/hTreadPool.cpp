#include "global.h"
#include "hThread.h"

namespace hThread
{
	hPool::hPool() : _valid(false), busyThd(0), cfgData("hThread.yml")
	{
		if (!cfgData.loadCfg())
		{//Err
			_valid = true;
			return;
		}
		init();
	}

	void hPool::init()
	{
		//for (const TaskMgrCfgItem& item : cfgData.taskMgrCfg)
		//	taskMgrs.emplace_back(item.second);
	}

	void hPool::final()
	{
	}

	void hPool::run()
	{
	}

	void hPool::stop()
	{
	}
}