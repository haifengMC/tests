#pragma once

namespace hThread
{
	class hTaskMgrBase : public hTool::hAutoPtrObj
	{
		DefLog_Init();
		hTaskMgr::hCfgData _cfg;
		hTaskMgr::hTaskMgrData _taskMgr;//<id-Task>id������
		hTaskMgr::hWeightMgrData _weightMgr;//Ȩ�ع���<task thisId>
		hTaskMgr::hStatMgrData _statMgr;//״̬����<thisId>
		hTaskMgr::hUpdateMgrData _updateMgr;//���ݸ��� ����id
	public:
		hTaskMgrBase(const TaskMgrCfgItem& base);
		~hTaskMgrBase();

	};


	class hTaskMgr : public hTool::hAutoPtrObj
	{
		const TaskMgrCfgItem& _base;

		hTool::hUniqueIdGen<size_t, hTask> _tasks;//<id-Task>id������
		hTool::hRWeightMap<size_t> _weights;//Ȩ�ع���<task thisId>
		WeightsMgr _weightsMgr;//Ȩ�ع���<task thisId>
		std::list<size_t> _states[TaskStatType::Max];//״̬����<thisId>
		hStatMgrData _stateMgr;//״̬����

		size_t _updateId = 0;//���ݸ��� ����id
	public:
		hTaskMgr(const TaskMgrCfgItem& base);
		~hTaskMgr();

		void init();

		//std::list<size_t>* getStateList(TaskStatType state) { return _stateMgr.getStateList(state); }
		std::list<size_t>* getStateList(TaskStatType state);

		//�ύ���񣬽��������ύ�����������ύ��Ĭ��״̬Ϊ�ȴ�
		template <size_t N>
		size_t commitTasks(PhTask(&task)[N]);
		size_t commitTasks(PhTask* task, size_t num);
		size_t commitTasks(PhTask& task);
		//׼�����񣬰�Ȩ��ȡ���ȴ��������������񣬷�������ָ��
		PhTask readyTasks(size_t busy);
		//������������
		template <typename ... Args >
		void updateTaskData(size_t taskId, size_t opt, Args ... args);

		//��������״̬
		bool updateTaskState(size_t tskId, std::list<size_t>::iterator& statIt,
			TaskStatType oldStat, TaskStatType newStat);
		//���������
		void pushTask2Weights(PWhTask pTask) { _weightsMgr.pushTask(pTask); }

	private:
		//�����������Ӻ���
		void addUpdateTaskFunc(size_t taskId, 
			std::function<bool()> checkFn,
			std::function<void()> execFn);

		void spliceTasks(TaskStatType from, TaskStatType to, const std::vector<size_t>& ids);

#if 0
		void spliceTasks(TaskStatType from, TaskStatType to, Task** pTask, size_t num);
		//�ƶ���������
		void spliceTasks(TaskStatType from, TaskStatType to);
#endif
	};
}
DefLog(hThread::hTaskMgr, _base, _tasks, _weights, _states);