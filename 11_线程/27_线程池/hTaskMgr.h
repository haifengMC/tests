#pragma once
#include "hTool.h"

namespace hThread
{
	class TaskMgr
	{
		friend class Task;

		const TaskMgrCfgItem& base;

		std::map <size_t, Task> tasks;//<id-Task>

		hTool::hUniqueIdGen<size_t, Task> tasksIdGen;//id������
		hTool::hRWeightMap<size_t> weights;//Ȩ�ع���<task thisId>
		std::list<Task*> states[TaskStatType::Max];//״̬����
	public:
		TaskMgr(const TaskMgrCfgItem& base);

		//�ύ���񣬽��������ύ�����������ύ��Ĭ��״̬Ϊ�ȴ�
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