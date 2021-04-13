#pragma once

#define	_PUTOUT_D

#include "hTool.h"
#include "hThreadCfg.h"

namespace hThread 
{
	struct hUserData;
	typedef hTool::hAutoPtr<hUserData> PhUserData;
	struct hUpdateData;
	typedef hTool::hWeakPtr<hUpdateData> PWhUpdDt;

	class hNode;
	typedef hTool::hAutoPtr<hNode> PhNode;
	typedef std::list<PhNode> hNodeList;
	typedef hNodeList::iterator hNodeListIt;

	namespace hTask
	{
		namespace hStatic
		{
			struct hAttrData;//属性数据
			struct hNodeData;//静态节点数据
		}
		//任务静态数据管理(属性、节点静态数据)
		class hStaticDataMgr;
		typedef hTool::hAutoPtr<hStaticDataMgr> PhStcDt;

		namespace hDynamic
		{
			struct hStatData;//任务状态数据
			struct hRunData;//任务运行数据
		}
		//任务动态数据管理(状态、运行数据)
		class hDynamicDataMgr;
		typedef hTool::hAutoPtr<hDynamicDataMgr> PhDynDt;
	}


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


