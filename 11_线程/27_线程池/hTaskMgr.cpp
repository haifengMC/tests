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
		COUT_LK(_base.index().getName() << " �������������...");
		_tasks.resize(10000, 99999);
	} 

	hTaskMgr::~hTaskMgr()
	{
		COUT_LK(_base.index().getName() << " ����������ͷ�...");
	}
	
	void hTaskMgr::init()
	{
		COUT_LK(_base.index().getName() << " �����������ʼ��...");
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

	//�ύ���񣬽��������ύ�����������ύ��Ĭ��״̬Ϊ�ȴ�
	size_t hTaskMgr::commitTasks(PhTask* tasks, size_t num)
	{

		size_t ret = 0;
		for (size_t n = 0; n < num; ++n)
		{
			PhTask pTask = tasks[n];
			if (!pTask)
				continue;

			if (!pTask->init(getThis<hTaskMgr>()))
				continue;//��ʼ������

			if (TaskStatType::Init != pTask->getDyn()->_stateTy)
				continue;//����ʼ��״̬

			if (!pTask->setStat(TaskStatType::Wait))
				continue;//�ύ��Ĭ��״̬Ϊ�ȴ�

			auto rsPair = _tasks.insert(pTask);

			if (!rsPair.second)
				continue;

			hTask& taskRef = *rsPair.first->second;
			++ret;

			//�����Ȩ�ع���
			if (!taskRef.checkAttr(TaskAttrType::Repeat) || taskRef.canRepeat())
				_weights.pushBack(taskRef.getWeight(), taskRef.getId());

			//�����״̬����
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

	//��������ָ��
	PhTask hTaskMgr::readyTasks(size_t busy)
	{
		//æµ�̳߳������æµ����
		if (busy >= _base.data.maxBusyThd)
			return PhTask();

		std::vector<size_t> tIds;
		_weights.getRandVal(tIds, 1);
		if (tIds.empty())
			return PhTask();

		PhTask pTask = _tasks.get(tIds[0]);
		if (!pTask)
		{
			COUT_LK(_base.index() << "�У�����" << tIds[0] << "�޴���...");
			return PhTask();
		}

		spliceTasks(TaskStatType::Wait, TaskStatType::Ready, tIds);
		return pTask;
	}

	//��������״̬
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

	void hTaskMgr::addUpdateTaskFunc(size_t taskId,
		std::function<bool()> checkFn,
		std::function<void()> execFn)
	{
		PhTask pUpdateTask = _tasks.get(_updateId);
		if (!pUpdateTask)
		{
			COUT_LK(_base.index() << "���ݸ��� ����δ��ʼ��,_updateId:" << _updateId << "...");
			return;
		}

		PWhUpdTsk pUpTask = pUpdateTask.dynamic<hUpdateTask>();
		if (!pUpTask)
		{
			COUT_LK(_base.index() << "���ݸ��� ����δ��ʼ��ΪUpdateTask����,_updateId:" << _updateId << "...");
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
