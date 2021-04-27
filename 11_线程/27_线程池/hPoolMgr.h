#pragma once

#include "hSingleton.h"

#ifdef _PUTOUT_D 
#define COL_END "\33[0m"
#define COL_RED "\33[31m"
#define COL_LIGHTRED "\33[91m"
#define COL_GREEN "\33[32m"
#define COL_LIGHTGREEN "\33[92m"
#define COL_DARKGREEN "\33[36m"
#define COL_LIGHTDARKGREEN "\33[96m"
#define COL_YELLOW "\33[33"
#define COL_LIGHTYELLOW "\33[93m"
#define COL_BLUE "\33[34m"
#define COL_LIGHTBLUE "\33[94m"
#define OUTCOL_GREEN(x) COL_GREEN << x << COL_END

#define MGR_MEM(id) COL_LIGHTGREEN << "MgrMem_" << id << COL_END
#define WORK_MEM(id) COL_LIGHTBLUE << "WorkMem_" << id << COL_END
#define TSK(id) COL_LIGHTRED << "Tsk_" << id << COL_END
#define NODE(id) COL_LIGHTDARKGREEN << "Node_" << id << COL_END
#define TSK_MGR(name) COL_LIGHTYELLOW << "TskMgr_" << name << COL_END

#define COUT_LK(x)\
	{\
		std::lock_guard<std::mutex> lk(shPoolMgr.getCoutM()); \
		std::ostringstream _os;\
		_os << x << std::endl;\
		std::ofstream of("ThreadLoop.log", std::ios::app);\
		of << _os.str().c_str();\
		of.close();\
	}
#else
#define OUTCOL_GREEN(x)
#define COUT_LK(x)
#endif // _PUTOUT_D 

namespace hThread
{
	class hPoolMgr : public Singleton<hPoolMgr>
	{
		bool _valid;
		ThreadPoolCfg cfgData;
		std::mutex coutM;//Êä³ö»¥³âËø
	public:
		operator bool() { return _valid; }

		hPoolMgr();

		std::mutex& getCoutM() { return coutM; }
		const ThreadBaseCfg& getBaseCfg() const { return cfgData.data.baseCfg; }
		const TaskMgrCfg& getTaskMgrCfg() const { return cfgData.data.taskMgrCfg; }

	};
#define shPoolMgr hThread::hPoolMgr::getMe()
}