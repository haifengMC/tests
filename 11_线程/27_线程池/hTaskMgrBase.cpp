#include "global.h"
#include "hTool.h"
#include "hThread.h"
#include "hPoolMgr.h"

namespace hThread
{
	
	void hTaskMgrBase::init(const TaskMgrCfgItem& base)
	{
		COUT_LK(base.index().getName() << " �����������ʼ��...");

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

	//�ύ���񣬽��������ύ�����������ύ��Ĭ��״̬Ϊ�ȴ�
	size_t hTaskMgrBase::commitTasks(PhTask* tasks, size_t num)
	{
		size_t ret = 0;
		for (size_t n = 0; n < num; ++n)
		{
			PhTask pTask = tasks[n];
			if (!pTask)
				continue;

			if (!pTask->init(getThis<hTaskMgrBase>()))
				continue;//��ʼ������

			if (pTask->checkStat(TaskStatType::Init))
				continue;//����ʼ��״̬

			auto rsPair = _pTaskMgr->insert(pTask);
			if (!rsPair.second)
				continue;

			++ret;

			//�ύ��Ĭ��״̬Ϊ�ȴ�
			pTask->setStat(TaskStatType::Wait)
			//�����Ȩ�ع���
			pushTask2Weight(pTask);
			//�����״̬����
			pTask->setStatIt(pushTask2Stat(pTask));
		}

		return ret;
	}

	size_t hTaskMgrBase::commitTasks(PhTask& task)
	{
		return commitTasks(&task, 1);
	}

	//��������ָ��
	PhTask hTaskMgrBase::readyTasks(size_t busy)
	{
		//æµ�̳߳������æµ����
		if (busy >= _pCfg->getMaxBusyThd())
			return PhTask();

		size_t tskId = _pWeightMgr->getTaskAtRand();
		if (!tskId)
			return PhTask();

		PhTask pTask = _tasks.get(tskId);
		if (!pTask)
		{
			COUT_LK(_pCfg->getName() << "�У�����" << tskId << "������...");
			return PhTask();
		}

		updateTaskState(tskId, pTask->getStatIt(), TaskStatType::Wait, TaskStatType::Ready);
		return pTask;
	}

	//��������״̬
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
			COUT_LK(_base.index() << "���ݸ��� ����δ��ʼ��,_updateId:" << _pUpdateMgr->getId() << "...");
			return;
		}

		PWhUpdTsk pUpTask = pUpdateTask.dynamic<hUpdateTask>();
		if (!pUpTask)
		{
			COUT_LK(_base.index() << "���ݸ��� ����δ��ʼ��ΪUpdateTask����,_updateId:" << _pUpdateMgr->getId() << "...");
			return;
		}

		pUpTask->updata(taskId, checkFn, execFn);
		_weights.pushBack(pUpTask->getWeight(), _updateId);
		shPool.notifyMgrThrd();
	}
}
