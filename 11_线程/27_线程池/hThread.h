#pragma once

#define	_PUTOUT_D

#include "hTool.h"
#include "hThreadCfg.h"

namespace hThread 
{
	struct hNodeData;
	typedef hTool::hAutoPtr<hNodeData> PhNodeData;
	struct hUpdateData;
	typedef hTool::hWeakPtr<hUpdateData> PWhUpdDt;

	class hNode;
	typedef hTool::hAutoPtr<hNode> PhNode;
	typedef std::list<PhNode> hNodeList;
	typedef hNodeList::iterator hNodeListIt;

	namespace hTask
	{
		struct hAttrData;//属性数据
		struct hStcNodeData;//静态节点数据
	}
	struct hTaskStaticData;
	typedef hTool::hAutoPtr<hTaskStaticData> PhTskStcDt;

	struct hTaskDynamicData;
	typedef hTool::hAutoPtr<hTaskDynamicData> PhTskDynDt;

	class hTask;
	typedef hTool::hAutoPtr<hTask> PhTask;
	typedef hTool::hWeakPtr<hTask> PWhTask;
	class hUpdateTask;
	typedef hTool::hWeakPtr<hUpdateTask> PWhUpdTsk;

	class hTaskMgr;
	typedef hTool::hAutoPtr<hTaskMgr> PhTaskMgr;
	typedef hTool::hWeakPtr<hTaskMgr> PWhTaskMgr;

	typedef hTool::hAutoPtr<std::thread> PThread;
	class hMem;
	typedef hTool::hAutoPtr<hMem> PhMem;
	class hMemWork;
	typedef hTool::hWeakPtr<hMemWork> PWhMemWork;
	typedef std::list<PWhMemWork> hMemWorkList;
	typedef hMemWorkList::iterator hMemWorkListIt;
}

#define Debug_PtrMap(os)\
	PhNodeData::debugMap(cout);\
	PhNode::debugMap(cout);\
	PhTskStcDt::debugMap(cout);\
	PhTskDynDt::debugMap(cout);\
	PhTask::debugMap(cout);\
	PhTaskMgr::debugMap(cout);\
	PThread::debugMap(cout);\
	PhMem::debugMap(cout);

#include "hRWLock.h"
#include "hDataBase.h"
#include "hNode.h"
#include "hTaskData.h"
#include "hTask.h"
#include "hUpdateTask.h"
#include "hTaskMgr.h"
#include "hMem.h"
#include "hMemWork.h"
#include "hMemMgr.h"
#include "hPool.h"

#include "hDataBaseImpl.h"
#include "hTaskImpl.h"
#include "hTaskMgrImpl.h"
#include "hPoolImpl.h"


