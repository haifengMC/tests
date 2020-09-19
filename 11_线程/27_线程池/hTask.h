#pragma once

namespace hThread
{
	class AllTasksData
	{
		std::map<size_t, TaskData> tasks;//<id-Task>

		hTool::hUniqueIdGen<size_t, TaskData> tasksIdGen;//id������
		hTool::hRWeightMap<TaskData*> weights;//Ȩ�ع���
		std::list<TaskData*> states[TaskStateType::Max];//״̬����
	public:
		AllTasksData();

		//�ύ���񣬽��������ύ�����������ύ��Ĭ��״̬Ϊ�ȴ�
		size_t commitTasks(Task** task, size_t num);
		//׼�����񣬰�Ȩ��ȡ���ȴ��������������񣬷���ȡ������
		size_t readyTasks(size_t num);
		//ȡ����׼������,����������Żصȴ�״̬
		void cancelReadyTasks();
		//ִ�����񣬾������񣬷���ʵ��ִ�е�����,numThr�����߳���
		size_t runTasks(size_t numThr, size_t rate);
		size_t pushTasks(Task** const& task, const size_t& num);
		size_t popTasks(Task** const& task, const size_t& num);
	};

	typedef std::list<TaskNode*> NodeList;
	typedef NodeList::iterator NodeListIt;

	typedef std::list<ThreadMem*> ThrdList;
	typedef ThrdList::iterator ThrdListIt;

	//��������(��̬����)
	struct TaskAttr
	{
		bool loop = false;//�Ƿ���ѭ������

		size_t weight = 0;//Ȩ��
		size_t thrdExpect = 0;//�ڴ��߳���

		NodeList nodeList;//�ڵ�����

		~TaskAttr() {}//��Ҫʵ������
	};

	//����״̬(����ʱ����)
	struct TaskStat
	{
		TaskStateType state = TaskStateType::Max;//��ǰ״̬
		std::list<Task*>::iterator stateIt;//ָ��ǰ״̬�ĵ�����

		ThrdList thrds;//��ǰ���и�������߳�
		NodeListIt nodeIt;//ָ��ǰ�����нڵ�

		~TaskStat() {}//��Ҫʵ������
	};

	class Task : public hTool::hUniqueMapVal<size_t, Task>
	{
		size_t thisId = 0;//����Ψһid

		hTool::hAutoPtr<TaskAttr> attr;
		hTool::hAutoPtr<TaskStat> stat;
	public:
		Task(hTool::hAutoPtr<TaskAttr> attr);
		Task(Task&& t);

		bool init();
		bool setStat(TaskStateType state);

		size_t getId() const { return thisId; }
		hTool::hAutoPtr<TaskAttr>& getAttr() { return attr; }
		hTool::hAutoPtr<TaskStat>& getStat() { return stat; }

		TaskNode* getNextNode();
		//����̵߳�����,��δ����
		void addThrd(ThreadMem* pMem);
		//����ʵ��ʹ�õ��߳���
		size_t runTask(const size_t& rate);
	private:
		bool check();//һ���Լ��
	};

}