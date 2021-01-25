#pragma once

namespace hThread
{
	class Task;
	class TaskMgr;
	class ThreadMem;
#if 0
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
#endif

	typedef hTool::hAutoPtr<TaskNode> PTaskNode;
	typedef std::list<PTaskNode> NodeList;
	typedef NodeList::iterator NodeListIt;

	//typedef std::list<ThreadMem*> ThrdList;
	//typedef ThrdList::iterator ThrdListIt;
	
	//��������(��̬����)
	struct TaskAttr
	{
		uint16_t _attr = 0;//�������ԣ���Ӧ TaskAttrType
		size_t _weight = 0;//Ȩ��
		size_t _thrdExpect = 0;//�ڴ��߳���

		size_t _incId = 0;//�ڵ����id
		hTool::hAutoPtr<NodeData> _nodeData;//�ڵ�����
		NodeList _nodeList;//�ڵ�����

		void setAttr(uint16_t attr = 0) { _attr = attr; }
		bool addNode(TaskNode* pNode);//��������ڵ�
		bool initNodeData(NodeData* pData = NULL);//��ʼ���ڵ�����

		std::ostream& debugShow(std::ostream& os, uint8_t n = 0, char c = '\t');
		TaskAttr(size_t weight, size_t thrdExpect, uint16_t attr);
	};
	//����״̬(����ʱ����)
	struct TaskStat
	{
		TaskStatType state = TaskStatType::Max;//��ǰ״̬
		std::list<Task*>::iterator stateIt;//ָ��ǰ״̬�ĵ�����

		//TaskMgr* pMgr = NULL;//ָ���Լ����ڹ�����
		//ThrdList thrds;//��ǰ���и�������߳�
		NodeListIt nodeIt;//ָ��ǰ�����нڵ�

		std::ostream& debugShow(std::ostream& os, uint8_t n = 0, char c = '\t');
		~TaskStat() {}//��Ҫʵ������
	};

	class Task : public hTool::hUniqueMapVal<size_t, Task>
	{
		size_t _thisId = 0;//����Ψһid

		hTool::hAutoPtr<TaskAttr> _attr;
		hTool::hAutoPtr<TaskStat> _stat;
	public:
		Task(size_t weight, size_t thrdExpect, uint16_t attr);
		Task(hTool::hAutoPtr<TaskAttr> attr);
		Task(Task&& t);

		bool init(/*TaskMgr* pMgr*/);

		/*
		��������
		*/

		//��������ڵ�
		bool addNode(TaskNode* pNode) { return _attr && _attr->addNode(pNode); }
		//��ʼ���ڵ�����
		bool initNodeData(NodeData* pData = NULL) { return _attr && _attr->initNodeData(pData); }

		bool setStat(TaskStatType state);

		size_t getId() const { return _thisId; }
		size_t getWeight() const;
		hTool::hAutoPtr<TaskAttr>& getAttr() { return _attr; }
		hTool::hAutoPtr<TaskStat>& getStat() { return _stat; }

		PTaskNode getNextNode();
		//����̵߳�����,��δ����
		//void addThrd(ThreadMem* pMem);
		//����ʵ��ʹ�õ��߳���
		//size_t runTask(const size_t& rate);

		std::ostream& debugShow(std::ostream& os, uint8_t n = 0, char c = '\t');
	private:
		bool check() const;//һ���Լ��
	};

}