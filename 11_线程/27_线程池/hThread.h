#pragma once

#define	_PUTOUT_D

#include "hTool.h"
#include "hThreadCfg.h"

namespace hThread 
{
	struct NodeData;
	typedef hTool::hAutoPtr<NodeData> PNodeData;
	struct UpdateTaskData;
	typedef hTool::hWeakPtr<UpdateTaskData> PWUpdTskDt;

	class TaskNode;
	typedef hTool::hAutoPtr<TaskNode> PTaskNode;
	typedef std::list<PTaskNode> NodeList;
	typedef NodeList::iterator NodeListIt;

	struct TaskAttr;
	typedef hTool::hAutoPtr<TaskAttr> PTaskAttr;

	struct TaskStat;
	typedef hTool::hAutoPtr<TaskStat> PTaskStat;

	class Task;
	typedef hTool::hAutoPtr<Task> PTask;
	typedef hTool::hWeakPtr<Task> PWTask;
	class UpdateTask;
	typedef hTool::hWeakPtr<UpdateTask> PWUpdTsk;

	class TaskMgr;
	typedef hTool::hAutoPtr<TaskMgr> PTaskMgr;
	typedef hTool::hWeakPtr<TaskMgr> PWTaskMgr;

	typedef hTool::hAutoPtr<std::thread> PThread;
	class ThreadMem;
	typedef hTool::hAutoPtr<ThreadMem> PThrdMem;
	class ThreadMemWork;
	typedef hTool::hWeakPtr<ThreadMemWork> PWThrdMemWork;
	typedef std::list<PWThrdMemWork> ThrdMemWorkList;
	typedef ThrdMemWorkList::iterator ThrdMemWorkListIt;
}

#define Debug_PtrMap(os)\
	PNodeData::debugMap(cout);\
	PTaskNode::debugMap(cout);\
	PTaskAttr::debugMap(cout);\
	PTaskStat::debugMap(cout);\
	PTask::debugMap(cout);\
	PTaskMgr::debugMap(cout);\
	PThread::debugMap(cout);\
	PThrdMem::debugMap(cout);


#include "hTaskNode.h"
#include "hTask.h"
#include "hUpdateTask.h"
#include "hTaskMgr.h"
#include "hRWLock.h"
#include "hThreadMem.h"
#include "hThreadMemWork.h"
#include "hThreadMemMgr.h"
#include "hThreadPool.h"

#include "hTaskImpl.h"
#include "hTaskMgrImpl.h"
#include "hThreadPoolImpl.h"


