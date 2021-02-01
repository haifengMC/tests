#pragma once
#include "hTool.h"

namespace hThread
{
	class TaskMgr
	{
		DefLog_Init();
		friend class Task;

		const TaskMgrCfgItem& _base;

		std::map <size_t, Task> _tasks;//<id-Task>
		hTool::hUniqueIdGen<size_t, Task> _tasksIdGen;//id������
		hTool::hRWeightMap<size_t> _weights;//Ȩ�ع���<task thisId>
		std::list<size_t> _states[TaskStatType::Max];//״̬����<thisId>
	public:
		TaskMgr(const TaskMgrCfgItem& base);

		//�ύ���񣬽��������ύ�����������ύ��Ĭ��״̬Ϊ�ȴ�
		template <size_t N>
		size_t commitTasks(Task (&task)[N]);
		size_t commitTasks(Task& task);
		size_t commitTasks(Task* task, size_t num);
#if 0

		//׼�����񣬰�Ȩ��ȡ���ȴ��������������񣬷���ȡ������
		size_t readyTasks(size_t num, size_t busy);
		//ȡ����׼������,����������Żصȴ�״̬
		void cancelReadyTasks();
		//ִ�����񣬾������񣬷���ʵ��ִ�е�����,numThr�����߳���
		size_t runTasks(size_t numThr, size_t rate);
#endif

#if 0
	private:
		void spliceTasks(TaskStateType from, TaskStateType to, Task** pTask, size_t num);
		void spliceTasks(TaskStateType from, TaskStateType to, const std::vector<Task*>& tDataVec);
		//�ƶ���������
		void spliceTasks(TaskStateType from, TaskStateType to);
#endif
	};
}
DefLog(hThread::TaskMgr, _base, _tasks, _weights, _states);