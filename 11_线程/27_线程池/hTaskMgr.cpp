#include "global.h"
#include "hTool.h"
#include "hThread.h"
#include "hPoolMgr.h"

namespace hThread
{
	std::list<size_t>* TaskStatMgr::getStateList(TaskStatType state)
	{
		if (TaskStatType::Max <= state)
			return NULL;

		std::list<size_t>* pList = NULL;
		readLk([&]() { pList = &_states[state]; });

		return pList;
	}

	bool TaskStatMgr::updateState(size_t tskId, std::list<size_t>::iterator& statIt,
		TaskStatType oldStat, TaskStatType newStat)
	{
		if (!tskId)
			return false;

		if (TaskStatType::Max <= oldStat)
			return false;

		if (TaskStatType::Max <= newStat)
			return false;

		if (oldStat == newStat)
			return false;

		writeLk([&]() 
			{
				std::list<size_t>& oldList = _states[oldStat];
				std::list<size_t>& newList = _states[newStat];

				if (!statIt._Ptr || statIt == oldList.end())
					statIt = newList.insert(newList.end(), tskId);
				else
					newList.splice(newList.end(), oldList, statIt);
			});

		return true;
	}

	hTaskMgr::hTaskMgr(const TaskMgrCfgItem& base) : 
		_base(base), _tasks(50)
	{ 
		COUT_LK(_base.index().getName() << " 任务管理器创建...");
		_tasks.resize(10000, 99999);
	} 

	hTaskMgr::~hTaskMgr()
	{
		COUT_LK(_base.index().getName() << " 任务管理器释放...");
	}
	
	void hTaskMgr::init()
	{
		COUT_LK(_base.index().getName() << " 任务管理器初始化...");
		PhTask pTsk;
		pTsk.bind(new hUpdateTask);
		commitTasks(pTsk);
		_updateId = pTsk->getId();
	}

	std::list<size_t>* hTaskMgr::getStateList(TaskStatType state)
	{
		if (TaskStatType::Max <= state)
			return NULL;

		return &_states[state];
	}

	//提交任务，将新任务提交给管理器，提交后默认状态为等待
	size_t hTaskMgr::commitTasks(PhTask* tasks, size_t num)
	{

		size_t ret = 0;
		for (size_t n = 0; n < num; ++n)
		{
			PhTask pTask = tasks[n];
			if (!pTask)
				continue;

			if (!pTask->init(getThis<hTaskMgr>()))
				continue;//初始化任务

			if (TaskStatType::Init != pTask->getDyn()->_stateTy)
				continue;//检测初始化状态

			if (!pTask->setStat(TaskStatType::Wait))
				continue;//提交后默认状态为等待

			auto rsPair = _tasks.insert(pTask);

			if (!rsPair.second)
				continue;

			hTask& taskRef = *rsPair.first->second;
			++ret;

			//添加至权重管理
			if (!taskRef.checkAttr(TaskAttrType::Repeat) || taskRef.canRepeat())
				_weights.pushBack(taskRef.getWeight(), taskRef.getId());

			//添加至状态管理
			auto& stRef = _states[TaskStatType::Wait];
			auto rsState = stRef.insert(stRef.end(), taskRef.getId());
			taskRef.getDyn()->_stateIt = rsState;
		}

		return ret;
	}

	size_t hTaskMgr::commitTasks(PhTask& task)
	{
		return commitTasks(&task, 1);
	}

	//返回任务指针
	PhTask hTaskMgr::readyTasks(size_t busy)
	{
		//忙碌线程超过最大忙碌限制
		if (busy >= _base.data.maxBusyThd)
			return PhTask();

		std::vector<size_t> tIds;
		_weights.getRandVal(tIds, 1);
		if (tIds.empty())
			return PhTask();

		PhTask pTask = _tasks.get(tIds[0]);
		if (!pTask)
		{
			COUT_LK(_base.index() << "中，任务" << tIds[0] << "无存在...");
			return PhTask();
		}

		spliceTasks(TaskStatType::Wait, TaskStatType::Ready, tIds);
		return pTask;
	}

	//更新任务状态
	bool hTaskMgr::updateTaskState(size_t tskId, std::list<size_t>::iterator& statIt,
		TaskStatType oldStat, TaskStatType newStat)
	{
		return _stateMgr.updateState(tskId, statIt, oldStat, newStat);
	}

#if 0

	void TaskMgr::cancelReadyTasks()
	{
		if (states[TaskStateType::Ready].empty())
			return;

		spliceTasks(TaskStateType::Ready, TaskStateType::Wait);
	}

	//返回分配了线程的任务数
	size_t TaskMgr::runTasks(size_t numThr, size_t rate)
	{
		if (!numThr || !rate)
			return 0;

		if (states[TaskStateType::Ready].empty())
			return 0;

		size_t ret = 0;

		for (auto itTData = states[TaskStateType::Ready].begin();
			itTData != states[TaskStateType::Ready].end(); ++itTData)
		{
			Task* pTask = *itTData;
			if (!pTask)//如果任务不存在，移入错误状态
			{
				spliceTasks(TaskStateType::Ready, TaskStateType::Error, &pTask, 1);
				continue;
			}

			//任务运行的线程
			size_t runThr = pTask->runTask(rate);
			if (!runThr)//无运行线程，移入等待状态
			{
				spliceTasks(TaskStateType::Ready, TaskStateType::Wait);
				break;
			}

			++ret;
			spliceTasks(TaskStateType::Ready, TaskStateType::Run, &pTask, 1);

			if (runThr >= numThr)//可用线程已耗尽
			{
				spliceTasks(TaskStateType::Ready, TaskStateType::Wait);
				break;
			}

			numThr -= runThr;
		}

		cancelReadyTasks();

		return ret;
	}
#endif

	void hTaskMgr::addUpdateTaskFunc(size_t taskId,
		std::function<bool()> checkFn,
		std::function<void()> execFn)
	{
		PhTask pUpdateTask = _tasks.get(_updateId);
		if (!pUpdateTask)
		{
			COUT_LK(_base.index() << "数据更新 任务未初始化,_updateId:" << _updateId << "...");
			return;
		}

		PWhUpdTsk pUpTask = pUpdateTask.dynamic<hUpdateTask>();
		if (!pUpTask)
		{
			COUT_LK(_base.index() << "数据更新 任务未初始化为UpdateTask对象,_updateId:" << _updateId << "...");
			return;
		}

		pUpTask->updata(taskId, checkFn, execFn);
		_weights.pushBack(pUpTask->getWeight(), _updateId);
		shPool.notifyMgrThrd();
	}

	void hTaskMgr::spliceTasks(TaskStatType from, TaskStatType to, const std::vector<size_t>& ids)
	{
		if (from >= TaskStatType::Max || to >= TaskStatType::Max || ids.empty())
			return;

		for (auto id : ids)
		{
			PhTask pTask = _tasks.get(id);
			if (!pTask)
				continue;

			if (!pTask->getDyn())
				continue;

			hTaskDynamicData& stat = *pTask->getDyn();
			if (from != stat._stateTy)
				continue;

			if (stat._stateIt == _states[from].end())
				continue;

			stat._stateTy = to;
			_states[to].splice(_states[to].begin(), _states[from], stat._stateIt);
		}
	}
#if 0

	void TaskMgr::spliceTasks(TaskStateType from, TaskStateType to, Task** pTask, size_t num)
	{
		if (from >= TaskStateType::Max || to >= TaskStateType::Max || !pTask || !num)
			return;

		for (size_t n = 0; n < num; ++n)
		{
			if (!pTask[n]->getStat())
				continue;

			TaskStat& stat = *pTask[n]->getStat();
			if (from != stat.state)
				continue;

			if (stat.stateIt == states[from].end())
				continue;

			stat.state = to;
			states[to].splice(states[to].begin(), states[from], stat.stateIt);
			//迭代器在粘接后仍然有效，无需再赋值
			//stat.stateIt = states[to].begin(); 
		}
	}

	void TaskMgr::spliceTasks(TaskStateType from, TaskStateType to)
	{
		if (from >= TaskStateType::Max || to >= TaskStateType::Max)
			return;

		if (states[from].empty())
			return;

		for (auto pData : states[from])
			pData->getStat()->state = to;

		states[to].splice(states[to].begin(), states[from]);
	}
#endif
}
