#pragma once
#include "hTool.h"

namespace hThread
{
	class TaskMgr : public hTool::hAutoPtrObj
	{
		DefLog_Init();
		friend class Task;

		const TaskMgrCfgItem& _base;

		hTool::hUniqueIdGen<size_t, Task> _tasks;//<id-Task>id������
		hTool::hRWeightMap<size_t> _weights;//Ȩ�ع���<task thisId>
		std::list<size_t> _states[TaskStatType::Max];//״̬����<thisId>

		size_t _updateId = 0;//���ݸ��� ����id
	public:
		TaskMgr(const TaskMgrCfgItem& base);
		~TaskMgr();

		void init();

		std::list<size_t>* getStateList(TaskStatType state);

		//�ύ���񣬽��������ύ�����������ύ��Ĭ��״̬Ϊ�ȴ�
		template <size_t N>
		size_t commitTasks(PTask(&task)[N]);
		size_t commitTasks(PTask* task, size_t num);
		size_t commitTasks(PTask& task);
		//׼�����񣬰�Ȩ��ȡ���ȴ��������������񣬷�������ָ��
		PTask readyTasks(size_t busy);
		//������������
		template <typename ... Args >
		void updateTaskData(size_t taskId, size_t opt, Args ... args);
#if 0

		//ȡ����׼������,����������Żصȴ�״̬
		void cancelReadyTasks();
		//ִ�����񣬾������񣬷���ʵ��ִ�е�����,numThr�����߳���
		size_t runTasks(size_t numThr, size_t rate);
#endif
	private:
		//�����������Ӻ���
		void addUpdateTaskFunc(std::function<void()> fn);

		void spliceTasks(TaskStatType from, TaskStatType to, const std::vector<size_t>& ids);

#if 0
		void spliceTasks(TaskStatType from, TaskStatType to, Task** pTask, size_t num);
		//�ƶ���������
		void spliceTasks(TaskStatType from, TaskStatType to);
#endif
	};
}
DefLog(hThread::TaskMgr, _base, _tasks, _weights, _states);