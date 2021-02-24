#pragma once
#include "hConfig.h"

//������������
BEG_ENUM(TaskAttrType)
{
	Loop,	//������
	Detach,	//��������������ɺ�ֱ�Ӷ���
	Repeat,	//��������������ɺ����ȴ����ȴ��´θ��ô���
	Max
}
END_ENUM(TaskAttrType, Max, Loop)

BEG_ENUM(TaskAttrTypeBit)
{
	Loop =		0x00000001,		//������
	Detach =	0x00000002,		//��������������ɺ�ֱ�Ӷ���
	Repeat =	0x00000004,		//��������������ɺ����ȴ����ȴ��´θ��ô���
	Max
}
END_ENUM(TaskAttrTypeBit, Max, Loop, Detach)

//����״̬����
BEG_ENUM(TaskStatType)
{
	Init,
	Wait,
	Ready,
	Run,
	Finish,
	Detach, //�����˷����������ɣ������߳��Ժ���ɾ��
	Error,
	Max
}
END_ENUM(TaskStatType, Max, Init, Wait, Ready, Run, Finish, Detach, Error)

//�̳߳�Ա����
BEG_ENUM(ThreadMemType)
{
	Work,//�����߳�
	Mgr,//�����߳�
	Max
}
END_ENUM(ThreadMemType, Max, Work, Mgr)

//�̳߳�Ա״̬����
BEG_ENUM(ThreadMemStatType)
{
	Init,//�ոմ�����û����
	Wait,//��ʼ���еȴ�����
	Ready,//�������׼������
	Run,//����������
	Max
}
END_ENUM(ThreadMemStatType, Max, Init, Wait, Ready, Run)

//�̻߳�������
BEG_CFGSTRUCT(ThreadBaseCfg)
{
	//�����߳�
	size_t initMgrThd = 0;
	//�����߳�
	size_t minThd = 0;
	size_t initThd = 0;
	size_t runThd = 0;
	size_t maxThd = 0;
}
END_CFGSTRUCT(ThreadBaseCfg, initMgrThd, minThd, initThd, runThd, maxThd)

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
	TaskMgrType tType = TaskMgrType::None;
	TaskMgrPriority priority = TaskMgrPriority::Max;
	size_t maxBusyThd = 0;//æµ�̳߳���������ޣ��򲻿ɷ�������
}
END_CFGMAP(TaskMgrCfg, TaskMgrPriority, priority, tType, maxBusyThd)

BEG_CFGDATA(ThreadPoolCfg)
{
	ThreadBaseCfg baseCfg;
	TaskMgrCfg taskMgrCfg;
}
END_CFGDATA(ThreadPoolCfg, baseCfg, taskMgrCfg)
