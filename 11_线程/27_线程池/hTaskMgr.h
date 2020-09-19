#pragma once
#include "hTool.h"

namespace hThread
{
	class TaskMgr
	{
		const TaskMgrCfgItem& base;

		std::map <size_t, Task> tasks;//<id-Task>

		hTool::hUniqueIdGen<size_t, Task> tasksIdGen;//id������
		hTool::hRWeightMap<Task*> weights;//Ȩ�ع���
		std::list<Task*> states[TaskStateType::Max];//״̬����
	public:
		TaskMgr(const TaskMgrCfgItem& base);

		//�ύ���񣬽��������ύ�����������ύ��Ĭ��״̬Ϊ�ȴ�
		size_t commitTasks(Task* task, size_t num);
		//׼�����񣬰�Ȩ��ȡ���ȴ��������������񣬷���ȡ������
		size_t readyTasks(size_t num, size_t busy);
		//ȡ����׼������,����������Żصȴ�״̬
		void cancelReadyTasks();
		size_t runTasks(size_t numThr, size_t rate);
		size_t pushTasks(Task** const& task, const size_t& num);
		size_t popTasks(Task** task, size_t begNum, size_t num, size_t busy);
	private:
		void spliceTasks(TaskStateType from, TaskStateType to, Task** pTask, size_t num);
		void spliceTasks(TaskStateType from, TaskStateType to, const std::vector<Task*>& tDataVec);
		//�ƶ���������
		void spliceTasks(TaskStateType from, TaskStateType to);
	};
}