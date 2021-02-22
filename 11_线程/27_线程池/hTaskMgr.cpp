#include "global.h"
#include "hTool.h"
#include "hThread.h"
#include "hThreadPoolMgr.h"

namespace hThread
{

	TaskMgr::TaskMgr(const TaskMgrCfgItem& base) : 
		_base(base), _tasks(50)
	{ 
		COUT_LK(_base.index().getName() << " �������������...");
		_tasks.resize(10000, 99999);
	} 

	TaskMgr::~TaskMgr()
	{
		COUT_LK(_base.index().getName() << " ����������ͷ�...");
	}

	std::list<size_t>* TaskMgr::getStateList(TaskStatType state)
	{
		if (TaskStatType::Max <= state)
			return NULL;

		return &_states[state];
	}

	//�ύ���񣬽��������ύ�����������ύ��Ĭ��״̬Ϊ�ȴ�
	size_t TaskMgr::commitTasks(PTask* tasks, size_t num)
	{

		size_t ret = 0;
		for (size_t n = 0; n < num; ++n)
		{
			PTask pTask = tasks[n];
			if (!pTask)
				continue;

			if (!pTask->init(*getThis<TaskMgr>()))
				continue;//��ʼ������

			if (TaskStatType::Init != pTask->getStat()->_stateTy)
				continue;//����ʼ��״̬

			if (!pTask->setStat(TaskStatType::Wait))
				continue;//�ύ��Ĭ��״̬Ϊ�ȴ�

			auto rsPair = _tasks.insert(pTask);

			if (!rsPair.second)
				continue;

			Task& taskRef = *rsPair.first->second;
			++ret;

			//�����Ȩ�ع���
			_weights.pushBack(taskRef.getWeight(), taskRef.getId());

			//�����״̬����
			auto& stRef = _states[TaskStatType::Wait];
			auto rsState = stRef.insert(stRef.end(), taskRef.getId());
			taskRef.getStat()->_stateIt = rsState;
		}

		return ret;
	}

	size_t TaskMgr::commitTasks(PTask& task)
	{
		return commitTasks(&task, 1);
	}

	//��������ָ��
	PTask TaskMgr::readyTasks(size_t busy)
	{
		//æµ�̳߳������æµ����
		if (busy >= _base.data.maxBusyThd)
			return PTask();

		std::vector<size_t> tIds;
		_weights.getRandVal(tIds, 1);
		if (tIds.empty())
			return PTask();

		PTask pTask = _tasks.get(tIds[0]);
		if (!pTask)
		{
			COUT_LK(_base.index() << "�У�����" << tIds[0] << "�޴���...");
			return PTask();
		}

		spliceTasks(TaskStatType::Wait, TaskStatType::Ready, tIds);
		return pTask;
	}

	void TaskMgr::updateTaskData(size_t taskId, byte opt, void* data)
	{
		PTask pTask = _tasks.get(taskId);
		if (!pTask)
			return;

	}

#if 0

	void TaskMgr::cancelReadyTasks()
	{
		if (states[TaskStateType::Ready].empty())
			return;

		spliceTasks(TaskStateType::Ready, TaskStateType::Wait);
	}

	//���ط������̵߳�������
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
			if (!pTask)//������񲻴��ڣ��������״̬
			{
				spliceTasks(TaskStateType::Ready, TaskStateType::Error, &pTask, 1);
				continue;
			}

			//�������е��߳�
			size_t runThr = pTask->runTask(rate);
			if (!runThr)//�������̣߳�����ȴ�״̬
			{
				spliceTasks(TaskStateType::Ready, TaskStateType::Wait);
				break;
			}

			++ret;
			spliceTasks(TaskStateType::Ready, TaskStateType::Run, &pTask, 1);

			if (runThr >= numThr)//�����߳��Ѻľ�
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

	void TaskMgr::spliceTasks(TaskStatType from, TaskStatType to, const std::vector<size_t>& ids)
	{
		if (from >= TaskStatType::Max || to >= TaskStatType::Max || ids.empty())
			return;

		for (auto id : ids)
		{
			PTask pTask = _tasks.get(id);
			if (!pTask)
				continue;

			if (!pTask->getStat())
				continue;

			TaskStat& stat = *pTask->getStat();
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
			//��������ճ�Ӻ���Ȼ��Ч�������ٸ�ֵ
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
