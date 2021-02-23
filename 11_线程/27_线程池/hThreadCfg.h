#pragma once
#include "hConfig.h"

//任务属性类型
BEG_ENUM(TaskAttrType)
{
	Loop,	//环任务
	Detach,	//分离任务，任务完成后直接丢弃
	Repeat,	//重复任务，任务完成后进入等待，等待下次重复处理
	Max
}
END_ENUM(TaskAttrType, Max, Loop)

BEG_ENUM(TaskAttrTypeBit)
{
	Loop = 0x00000001,		//环任务
	Detach = 0x00000002,	//分离任务，任务完成后直接丢弃
	Repeat = 0x00000004,	//重复任务，任务完成后进入等待，等待下次重复处理
	Max
}
END_ENUM(TaskAttrTypeBit, Max, Loop, Detach)

//任务状态类型
BEG_ENUM(TaskStatType)
{
	Init,
	Wait,
	Ready,
	Run,
	Finish,
	Detach, //设置了分离的任务完成，管理线程稍后将其删除
	Error,
	Max
}
END_ENUM(TaskStatType, Max, Init, Wait, Ready, Run, Finish, Detach, Error)

//线程成员类型
BEG_ENUM(ThreadMemType)
{
	Work,//工作线程
	Mgr,//管理线程
	Max
}
END_ENUM(ThreadMemType, Max, Work, Mgr)

//线程成员状态类型
BEG_ENUM(ThreadMemStatType)
{
	Init,//刚刚创建还没运行
	Wait,//开始运行等待任务
	Ready,//填充任务准备处理
	Run,//处理任务中
	Max
}
END_ENUM(ThreadMemStatType, Max, Init, Wait, Ready, Run)

//线程基础配置
BEG_CFGSTRUCT(ThreadBaseCfg)
{
	//管理线程
	size_t initMgrThd = 0;
	//工作线程
	size_t minThd = 0;
	size_t initThd = 0;
	size_t runThd = 0;
	size_t maxThd = 0;
}
END_CFGSTRUCT(ThreadBaseCfg, initMgrThd, minThd, initThd, runThd, maxThd)

BEG_ENUM(TaskMgrType)
{
	None,
	Initiative,	//运行，主动线程到达某值阻塞，运行不可被阻塞
	Passive,//阻塞，主动线程不足某值运行，运行可被主动线程阻塞
}
END_ENUM(TaskMgrType, None, Initiative, Passive)

BEG_ENUM(TaskMgrPriority)
{
	Highest,
	Higher,
	High,
	Normal,
	Low,
	Lower,
	Lowest,
	Max
}
END_ENUM(TaskMgrPriority, Max, Highest, Higher, High, Normal, Low, Lower, Lowest)

BEG_CFGMAP(TaskMgrCfg)
{
	TaskMgrType tType = TaskMgrType::None;
	TaskMgrPriority priority = TaskMgrPriority::Max;
	size_t maxBusyThd = 0;//忙碌线程超过最大上限，则不可分配任务
}
END_CFGMAP(TaskMgrCfg, TaskMgrPriority, priority, tType, maxBusyThd)

BEG_CFGDATA(ThreadPoolCfg)
{
	ThreadBaseCfg baseCfg;
	TaskMgrCfg taskMgrCfg;
}
END_CFGDATA(ThreadPoolCfg, baseCfg, taskMgrCfg)
