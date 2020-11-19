#pragma once

#include "hSingleton.h"

namespace hThread
{
	class ThreadPoolMgr : public Singleton<ThreadPoolMgr>
	{
		bool _valid;
		ThreadPoolCfg cfgData;
	public:
		operator bool() { return _valid; }

		ThreadPoolMgr();

		const TreadBaseCfg& getBaseCfg() const { return cfgData.baseCfg; }
		const TaskMgrCfg& getTaskMgrCfg() const { return cfgData.taskMgrCfg; }

	};
#define sTreadPoolMgr hThread::ThreadPoolMgr::getMe()
}