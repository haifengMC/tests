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
	class hTaskBase;
	typedef hTool::hAutoPtr<hTaskBase> PhTask;
	typedef hTool::hWeakPtr<hTaskBase> PWhTask;
	class hUpdateTask;
	typedef hTool::hWeakPtr<hUpdateTask> PWhUpdTsk;

	namespace hTaskMgr
	{
		class hCfgData;//配置数据
		typedef hTool::hAutoPtr<hCfgData> PhCfgDt;
		class hTaskMgrData;//任务管理数据
		typedef hTool::hAutoPtr<hTaskMgrData> PhTskMgrDt;
		class hWeightMgrData;//权重管理数据
		typedef hTool::hAutoPtr<hWeightMgrData> PhWtMgrDt;
		class hStatMgrData;//状态管理数据
		typedef hTool::hAutoPtr<hStatMgrData> PhStatMgrDt;
		class hUpdateMgrData;//更新管理数据
		typedef hTool::hAutoPtr<hUpdateMgrData> PhUpMgrDt;
	}
	class hTaskMgrBase;
	typedef hTool::hAutoPtr<hTaskMgrBase> PhTaskMgr;
	typedef hTool::hWeakPtr<hTaskMgrBase> PWhTaskMgr;

	typedef hTool::hAutoPtr<std::thread> PThread;
	class hMemBase;
	typedef hTool::hAutoPtr<hMemBase> PhMemBase;
	class hWorkMem;
	typedef hTool::hWeakPtr<hWorkMem> PWhWorkMem;
	typedef std::list<PWhWorkMem> hWorkMemList;
	typedef hWorkMemList::iterator hWorkMemListIt;
}

#define Debug_PtrMap(os)
	//PhNodeData::debugMap(cout);\
	//PhNode::debugMap(cout);\
	//PhTskStcDt::debugMap(cout);\
	//PhTskDynDt::debugMap(cout);\
	//PhTask::debugMap(cout);\
	//PhTaskMgr::debugMap(cout);\
	//PThread::debugMap(cout);\
	//PhMem::debugMap(cout);

#include "hRWLock.h"
#include "hDataBase.h"
#include "hNode.h"

#include "hTaskData.h"
#include "hTaskBase.h"
#include "hUpdateTask.h"

#include "hTaskMgrData.h"
#include "hTaskMgrBase.h"

#include "hMem.h"
#include "hWorkMem.h"
#include "hMgrMem.h"
#include "hPool.h"

#include "hDataBaseImpl.h"
#include "hTaskDataImpl.h"
#include "hTaskBaseImpl.h"
#include "hTaskMgrBaseImpl.h"
#include "hPoolImpl.h"


