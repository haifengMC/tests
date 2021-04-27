#include "global.h"
#include "hTool.h"
#include "hThread.h"
#include "hPoolMgr.h"

namespace hThread
{
	
	void hTaskMgrBase::init(const TaskMgrCfgItem* base)
	{
		COUT_LK("任务管理器" << TSK_MGR(base->index().getName()) << "初始化...");

		_pCfg.emplace(getThis<hTaskMgrBase>(), base);
		_pTaskMgr.emplace(getThis<hTaskMgrBase>());
		_pWeightMgr.emplace(getThis<hTaskMgrBase>());
		_pStatMgr.emplace(getThis<hTaskMgrBase>());
		_pUpdateMgr.emplace(getThis<hTaskMgrBase>());

		PhTask pTsk;
		pTsk.bind(new hUpdateTask);
		commitTasks(pTsk);
		_pUpdateMgr->setId(pTsk->getId());
		_pUpdateMgr->setWeight(pTsk->getWeight());
	}

	const char* hTaskMgrBase::getName() const
	{
		if (!_pCfg)
			return NULL;

		return _pCfg->getName();
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

			if (!pTask->checkStat(TaskStatType::Init))
				continue;//检测初始化状态

			auto rsPair = _pTaskMgr->insertTask(pTask);
			if (!rsPair.second)
				continue;

			++ret;

			//提交后默认状态为等待
			pTask->setStat(TaskStatType::Wait);
			//添加至权重管理
			if (pTask->checkAttr(TaskAttrType::Repeat) 
				&& pTask->canRepeat())
				pushTask2Weight(pTask);
			//添加至状态管理
			auto it = pushTask2Stat(pTask);
			pTask->setStatIt(it);
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
		{
			COUT_LK(getName() << "忙碌线程超过最大忙碌限制(" << busy << "/" << _pCfg->getMaxBusyThd() << ")...")
			return PhTask();
		}

		size_t tskId = _pWeightMgr->getTaskAtRand();
		if (!tskId)
			return PhTask();

		PhTask pTask = _pTaskMgr->getTask(tskId);
		if (!pTask)
		{
			COUT_LK(TSK_MGR(_pCfg->getName()) << "中，任务" << TSK(tskId) << "不存在...");
			return PhTask();
		}

		pTask->updateStat(TaskStatType::Ready);
		return pTask;
	}

	//更新任务状态
	bool hTaskMgrBase::updateTaskState(size_t tskId, std::list<size_t>::iterator statIt,
		TaskStatType oldStat, TaskStatType newStat)
	{
		return _pStatMgr->updateState(tskId, statIt, oldStat, newStat);
	}

	void hTaskMgrBase::updateTaskData(size_t taskId, size_t opt, const void* data, size_t len)
	{
		void* tmpData = malloc(len);
		if (!tmpData)
		{
			COUT_LK(getName() << " 更新" <<
				"Tsk_" << taskId << "数据失败(" <<
				"opt:" << opt << ", len:" << len << ")，" <<
				"创建存储空间失败...");
			return;
		}
		memset(tmpData, 0, len);
		memcpy(tmpData, data, len);

		addUpdateTaskFunc(
			taskId,
			std::function<bool()>(std::bind(
				[&](size_t id)
				{
					PhTask pTask = _pTaskMgr->getTask(id);
					if (!pTask)
						return false;

					return pTask->checkStat(TaskStatType::Wait);
				}, taskId)),
			std::function<void()>(std::bind(
				[&](size_t id, void* tmpData,
					std::function<void(PWhUserDt, void*)> memFn)
				{
					PhTask pTask = _pTaskMgr->getTask(id);
					if (!pTask)
						return;

					PWhUserDt pData = pTask->getUserData();
					if (!pData)
						return;

					pData->writeLk([&]() { memFn(pData, tmpData); });
					free(tmpData);
					pushTask2Weight(pTask);
				}, taskId, tmpData,
				std::function<void(PWhUserDt, void*)>(bind(
					std::mem_fn(&hUserData::update),
					std::placeholders::_1, opt, 
					std::placeholders::_2, len)))));
	}

	void hTaskMgrBase::addUpdateTaskFunc(size_t taskId,
		std::function<bool()> checkFn,
		std::function<void()> execFn)
	{
		PhTask pUpdateTask = _pTaskMgr->getTask(_pUpdateMgr->getId());
		if (!pUpdateTask)
		{
			COUT_LK(_pCfg->getName() << "数据更新 任务未初始化,_updateId:" << _pUpdateMgr->getId() << "...");
			return;
		}

		PWhUpdTsk pUpTask = pUpdateTask.dynamic<hUpdateTask>();
		if (!pUpTask)
		{
			COUT_LK(_pCfg->getName() << "数据更新 任务未初始化为UpdateTask对象,_updateId:" << _pUpdateMgr->getId() << "...");
			return;
		}

		pUpTask->update(taskId, checkFn, execFn);
		pushTask2Weight(pUpdateTask);
		shPool.notifyMgrThrd();
	}

	bool hTaskMgrBase::pushUpTask2Weight(size_t taskId)
	{
		if (taskId == _pUpdateMgr->getId())
			return false;

		_pWeightMgr->pushTask(
			_pUpdateMgr->getWeight(), 
			_pUpdateMgr->getId()); 

		return true;
	}
}
