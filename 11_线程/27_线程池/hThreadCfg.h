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

BEG_ENUM(TaskStateType)
{
	Init,
	Wait,
	Ready,
	Run,
	Finish,
	Error,
	Max
}
END_ENUM(TaskStateType, Init, Wait, Ready, Run, Finish, Error, Max)

BEG_ENUM(TaskMgrType)
{
	None,
	Initiative,	//���У������̵߳���ĳֵ���������в��ɱ�����
	Passive,//�����������̲߳���ĳֵ���У����пɱ������߳�����
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
	DECL_CFGMAP(TaskMgrPriority, priority);

	TaskMgrType tType = TaskMgrType::None;
	TaskMgrPriority priority = TaskMgrPriority::Max;
	size_t maxBusyThd = 0;//æµ�̳߳���������ޣ��򲻿ɷ�������
}
END_CFGMAP(TaskMgrCfg, TaskMgrPriority, priority, tType, maxBusyThd)

BEG_CFGDATA(ThreadPoolCfg)
{
	DECL_CFGDATA(ThreadPoolCfg, baseCfg, taskMgrCfg);

	TreadBaseCfg baseCfg;
	TaskMgrCfg taskMgrCfg;
}
END_CFGDATA()

