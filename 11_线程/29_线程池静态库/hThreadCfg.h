#pragma once
#include "hConfig.h"

BEG_CFGSTRUCT(TreadBaseCfg)
{
	size_t minThd = 0;
	size_t initThd = 0;
	size_t runThd = 0;
	size_t maxThd = 0;
}
END_CFGSTRUCT(TreadBaseCfg, minThd, initThd, runThd, maxThd)

//BEG_ENUM(TaskMgrType)
//{
//	None,
//	Initiative,	//运行，busyThd到达某值阻塞
//	Passive,//阻塞，busyThd不足某值运行
//}
//END_ENUM(TaskMgrType, None, Initiative, Passive)
//
//BEG_ENUM(TaskMgrPriority)
//{
//	Highest,
//	Higher,
//	High,
//	Normal,
//	Low,
//	Lower,
//	Lowest,
//	Max
//}
//END_ENUM(TaskMgrPriority, Max, Highest, Higher, High, Normal, Low, Lower, Lowest)
//
//BEG_CFGMAP(TaskMgrCfg)
//{
//	DECL_CFGMAP(TaskMgrPriority, priority);
//
//	TaskMgrType tType = TaskMgrType::None;
//	TaskMgrPriority priority = TaskMgrPriority::Max;
//}
//END_CFGMAP(TaskMgrCfg, TaskMgrPriority, priority, tType)

BEG_CFGDATA(TreadPoolCfg)
{
	DECL_CFGDATA(TreadPoolCfg);

	TreadBaseCfg baseCfg;
	//TaskMgrCfg taskMgrCfg;
}
END_CFGDATA(TreadPoolCfg, baseCfg)

