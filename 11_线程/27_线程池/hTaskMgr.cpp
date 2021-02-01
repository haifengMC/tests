#include "global.h"
#include "hTool.h"
#include "hThread.h"

namespace hThread
{

	TaskMgr::TaskMgr(const TaskMgrCfgItem& base) : 
		_base(base), _tasksIdGen(_tasks, 50)
	{ 
		_tasksIdGen.resize(10000, 99999);
	} 

	size_t TaskMgr::commitTasks(Task& task)
	{
		return commitTasks(&task, 1);
	}

	//提交任务，将新任务提交给管理器，提交后默认状态为等待
	size_t TaskMgr::commitTasks(Task* task, size_t num)
	{
		size_t ret = 0;
		for (size_t n = 0; n < num; ++n)
		{
			Task&& taskRRef = std::move(task[n]);
			if (!taskRRef.init(this))
				continue;//初始化任务

			if (TaskStatType::Init != taskRRef.getStat()->_stateTy)
				continue;//检测初始化状态

			if (!taskRRef.setStat(TaskStatType::Wait))
				continue;//提交后默认状态为等待

			auto rsPair = _tasksIdGen.insert(taskRRef);

			if (!rsPair.second)
				continue;

			Task& taskRef = rsPair.first->second;
			++ret;

			//添加至权重管理
			_weights.pushBack(taskRef.getWeight(), taskRef.getId());

			//添加至状态管理
			auto& stRef = _states[TaskStatType::Wait];
			auto rsState = stRef.insert(stRef.end(), taskRef.getId());
			taskRef.getStat()->_stateIt = rsState;
		}

		return ret;
	}
#if 0

	//返回已就绪的可用任务数
	size_t TaskMgr::readyTasks(size_t num, size_t busy)
	{
		//忙碌线程超过最大忙碌限制
		if (busy >= base.maxBusyThd)
			return 0;

		//需要弹出的任务
		size_t needNum =
			base.maxBusyThd - busy < num ?
			base.maxBusyThd - busy : num;

		if (!needNum)
			return 0;

		std::vector<Task*> tDataVec;
		size_t ret = RANDOM(hTool::RandomType::UniformDeInt, tDataVec, num, weights);
		spliceTasks(TaskStateType::Wait, TaskStateType::Ready, tDataVec);

		return ret;
	}

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

	void TaskMgr::spliceTasks(TaskStateType from, TaskStateType to, const std::vector<Task*>& tDataVec)
	{
		if (from >= TaskStateType::Max || to >= TaskStateType::Max || tDataVec.empty())
			return;

		for (auto pData : tDataVec)
		{
			if (!pData->getStat())
				continue;

			TaskStat& stat = *pData->getStat();
			if (from != stat.state)
				continue;

			if (stat.stateIt == states[from].end())
				continue;

			stat.state = to;
			states[to].splice(states[to].begin(), states[from], stat.stateIt);
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
