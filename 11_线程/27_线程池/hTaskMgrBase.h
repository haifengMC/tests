#pragma once

namespace hThread
{
	class hTaskMgrBase : public hTool::hAutoPtrObj
	{
		DefLog_Init();
		hTaskMgr::PhCfgDt _pCfg;
		hTaskMgr::PhTskMgrDt _pTaskMgr;//<id-Task>id������
		hTaskMgr::PhWtMgrDt _pWeightMgr;//Ȩ�ع���<task thisId>
		hTaskMgr::PhStatMgrDt _pStatMgr;//״̬����<thisId>
		hTaskMgr::PhUpMgrDt _pUpdateMgr;//���ݸ��� ����id
	public:
		void init(const TaskMgrCfgItem* base);
		const char* getName() const;

		//�ύ���񣬽��������ύ�����������ύ��Ĭ��״̬Ϊ�ȴ�
		template <size_t N>
		size_t commitTasks(PhTask(&task)[N]);
		size_t commitTasks(PhTask* task, size_t num);
		size_t commitTasks(PhTask& task);
		//׼�����񣬰�Ȩ��ȡ���ȴ��������������񣬷�������ָ��
		PhTask readyTasks(size_t busy);
		//��������״̬
		bool updateTaskState(size_t tskId, std::list<size_t>::iterator statIt,
			TaskStatType oldStat, TaskStatType newStat);
		//������������
		void updateTaskData(size_t taskId, size_t opt, const void* data, size_t len);
		//�����������Ӻ���
		void addUpdateTaskFunc(size_t taskId,
			std::function<bool()> checkFn,
			std::function<void()> execFn);

		//���������Ȩ�ع���
		void pushTask2Weight(PhTask pTask) { _pWeightMgr->pushTask(pTask); }
		void pushTask2Weight(PWhTask pTask) { _pWeightMgr->pushTask(pTask); }
		bool pushUpTask2Weight(size_t taskId);
		//���������״̬����
		std::list<size_t>::iterator pushTask2Stat(PhTask pTask) { return _pStatMgr->pushTask(pTask); }
	};
}
DefLog(hThread::hTaskMgrBase, _pCfg, _pTaskMgr, _pWeightMgr, _pStatMgr, _pUpdateMgr);