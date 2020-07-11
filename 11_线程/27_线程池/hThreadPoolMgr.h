#pragma once

#include "hSingleton.h"

namespace hThread
{
	class ThreadPoolMgr : public Singleton<ThreadPoolMgr>
	{
		bool _invalid;
		ThreadPoolCfg cfgData;
	public:
		operator bool() { return _invalid; }

		ThreadPoolMgr();

		const TreadBaseCfg& getBaseCfg() const { return cfgData.baseCfg; }
		const TaskMgrCfg& getTaskMgrCfg() const { return cfgData.taskMgrCfg; }

	};
#define sTreadPoolMgr hThread::ThreadPoolMgr::getMe()
}