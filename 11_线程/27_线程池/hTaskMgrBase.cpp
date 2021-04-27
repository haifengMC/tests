#include "global.h"
#include "hTool.h"
#include "hThread.h"
#include "hPoolMgr.h"

namespace hThread
{
	
	void hTaskMgrBase::init(const TaskMgrCfgItem* base)
	{
		COUT_LK("���������" << TSK_MGR(base->index().getName()) << "��ʼ��...");

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

			if (!pTask->checkStat(TaskStatType::Init))
				continue;//����ʼ��״̬

			auto rsPair = _pTaskMgr->insertTask(pTask);
			if (!rsPair.second)
				continue;

			++ret;

			//�ύ��Ĭ��״̬Ϊ�ȴ�
			pTask->setStat(TaskStatType::Wait);
			//�����Ȩ�ع���
			if (pTask->checkAttr(TaskAttrType::Repeat) 
				&& pTask->canRepeat())
				pushTask2Weight(pTask);
			//�����״̬����
			auto it = pushTask2Stat(pTask);
			pTask->setStatIt(it);
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
		{
			COUT_LK(getName() << "æµ�̳߳������æµ����(" << busy << "/" << _pCfg->getMaxBusyThd() << ")...")
			return PhTask();
		}

		size_t tskId = _pWeightMgr->getTaskAtRand();
		if (!tskId)
			return PhTask();

		PhTask pTask = _pTaskMgr->getTask(tskId);
		if (!pTask)
		{
			COUT_LK(TSK_MGR(_pCfg->getName()) << "�У�����" << TSK(tskId) << "������...");
			return PhTask();
		}

		pTask->updateStat(TaskStatType::Ready);
		return pTask;
	}

	//��������״̬
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
			COUT_LK(getName() << " ����" <<
				"Tsk_" << taskId << "����ʧ��(" <<
				"opt:" << opt << ", len:" << len << ")��" <<
				"�����洢�ռ�ʧ��...");
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
			COUT_LK(_pCfg->getName() << "���ݸ��� ����δ��ʼ��,_updateId:" << _pUpdateMgr->getId() << "...");
			return;
		}

		PWhUpdTsk pUpTask = pUpdateTask.dynamic<hUpdateTask>();
		if (!pUpTask)
		{
			COUT_LK(_pCfg->getName() << "���ݸ��� ����δ��ʼ��ΪUpdateTask����,_updateId:" << _pUpdateMgr->getId() << "...");
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
