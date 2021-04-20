#include "global.h"
#include "hTool.h"
#include "hThread.h"
#include "hPoolMgr.h"

namespace hThread
{
	
	void hTaskMgrBase::init(const TaskMgrCfgItem& base)
	{
		COUT_LK(base.index().getName() << " 任务管理器初始化...");

		_pCfg.emplace(getThis<hTaskMgrBase>(), base);
		_pTaskMgr.emplace(getThis<hTaskMgrBase>());
		_pWeightMgr.emplace(getThis<hTaskMgrBase>());
		_pStatMgr.emplace(getThis<hTaskMgrBase>());
		_pUpdateMgr.emplace(getThis<hTaskMgrBase>());

		PhTask pTsk;
		pTsk.bind(new hUpdateTask);
		commitTasks(pTsk);
		_pUpdateMgr->setId(pTsk->getId());
	}

	//提交任务，将新任务提交给管理器，提交后默认状态为等待
	size_t hTaskMgrBase::commitTasks(PhTask* tasks, size_t num)
	{
		size_t ret = 0;
		for (size_t n = 0; n < num; ++n)
		{
			PhTask pTask = tasks[n];
			if (!pTask)
				continue;

			if (!pTask->init(getThis<hTaskMgrBase>()))
				continue;//初始化任务

			if (pTask->checkStat(TaskStatType::Init))
				continue;//检测初始化状态

			auto rsPair = _pTaskMgr->insert(pTask);
			if (!rsPair.second)
				continue;

			++ret;

			//提交后默认状态为等待
			pTask->setStat(TaskStatType::Wait)
			//添加至权重管理
			pushTask2Weight(pTask);
			//添加至状态管理
			pTask->setStatIt(pushTask2Stat(pTask));
		}

		return ret;
	}

	size_t hTaskMgrBase::commitTasks(PhTask& task)
	{
		return commitTasks(&task, 1);
	}

	//返回任务指针
	PhTask hTaskMgrBase::readyTasks(size_t busy)
	{
		//忙碌线程超过最大忙碌限制
		if (busy >= _pCfg->getMaxBusyThd())
			return PhTask();

		size_t tskId = _pWeightMgr->getTaskAtRand();
		if (!tskId)
			return PhTask();

		PhTask pTask = _tasks.get(tskId);
		if (!pTask)
		{
			COUT_LK(_pCfg->getName() << "中，任务" << tskId << "不存在...");
			return PhTask();
		}

		updateTaskState(tskId, pTask->getStatIt(), TaskStatType::Wait, TaskStatType::Ready);
		return pTask;
	}

	//更新任务状态
	bool hTaskMgrBase::updateTaskState(size_t tskId, std::list<size_t>::iterator statIt,
		TaskStatType oldStat, TaskStatType newStat)
	{
		return _pStatMgr->updateState(tskId, statIt, oldStat, newStat);
	}

	void hTaskMgrBase::addUpdateTaskFunc(size_t taskId,
		std::function<bool()> checkFn,
		std::function<void()> execFn)
	{
		PhTask pUpdateTask = _tasks.get(_pUpdateMgr->getId());
		if (!pUpdateTask)
		{
			COUT_LK(_base.index() << "数据更新 任务未初始化,_updateId:" << _pUpdateMgr->getId() << "...");
			return;
		}

		PWhUpdTsk pUpTask = pUpdateTask.dynamic<hUpdateTask>();
		if (!pUpTask)
		{
			COUT_LK(_base.index() << "数据更新 任务未初始化为UpdateTask对象,_updateId:" << _pUpdateMgr->getId() << "...");
			return;
		}

		pUpTask->updata(taskId, checkFn, execFn);
		_weights.pushBack(pUpTask->getWeight(), _updateId);
		shPool.notifyMgrThrd();
	}
}
