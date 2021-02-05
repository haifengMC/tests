#pragma once

#define	_PUTOUT_D

#include "hTool.h"
#include "hThreadCfg.h"

namespace hThread 
{
	struct NodeData;
	typedef hTool::hAutoPtr<NodeData> PNodeData;

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

	class TaskMgr;
	typedef hTool::hAutoPtr<TaskMgr> PTaskMgr;

	class ThreadMem;
	typedef hTool::hAutoPtr<ThreadMem> PThrdMem;
	typedef std::list<PThrdMem> ThrdMemList;
	typedef ThrdMemList::iterator ThrdMemListIt;
	class ThreadMemWork;
	typedef hTool::hWeakPtr<ThreadMemWork> PWThrdMemWork;
}

#include "hTaskNode.h"
#include "hTask.h"
#include "hTaskImpl.h"
#include "hTaskMgr.h"
#include "hTaskMgrImpl.h"
#include "hRWLock.h"
#include "hThreadMem.h"
#include "hThreadPool.h"
#include "hThreadPoolImpl.h"
