#pragma once

#include "hSingleton.h"

#ifdef _PUTOUT_D 
#define COUT_LK(x)\
	{\
		std::lock_guard<std::mutex> lk(sThrdPoolMgr.getCoutM()); \
		std::ostringstream _os;\
		_os << x << std::endl;\
		std::ofstream of("ThreadLoop.log", std::ios::app);\
		of << _os.str().c_str();\
		of.close();\
	}
#else
#define COUT_LK(x)
#endif // _PUTOUT_D 

namespace hThread
{
	class ThreadPoolMgr : public Singleton<ThreadPoolMgr>
	{
		bool _valid;
		ThreadPoolCfg cfgData;
		std::mutex coutM;//Êä³ö»¥³âËø
	public:
		operator bool() { return _valid; }

		ThreadPoolMgr();

		std::mutex& getCoutM() { return coutM; }
		const ThreadBaseCfg& getBaseCfg() const { return cfgData.data.baseCfg; }
		const TaskMgrCfg& getTaskMgrCfg() const { return cfgData.data.taskMgrCfg; }

	};
#define sThrdPoolMgr hThread::ThreadPoolMgr::getMe()
}