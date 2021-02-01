#include "global.h"
#include "hThread.h"

namespace hThread
{
	ThreadPool::ThreadPool() : _valid(false), busyThd(0), cfgData("hThread.yml")
	{
		if (!cfgData.loadCfg())
		{//Err
			_valid = true;
			return;
		}
		init();
	}

	void ThreadPool::init()
	{
		//for (const TaskMgrCfgItem& item : cfgData.taskMgrCfg)
		//	taskMgrs.emplace_back(item.second);
	}

	void ThreadPool::final()
	{
	}

	void ThreadPool::run()
	{
	}

	void ThreadPool::stop()
	{
	}
}