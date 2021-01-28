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
		DefLog_Init();
		size_t _weight = 0;//Ȩ��
		size_t _thrdExpect = 0;//�ڴ��߳���

		size_t _incId = 0;//�ڵ����id
		std::bitset<TaskAttrType::Max> _attr;//�������ԣ���Ӧ TaskAttrType
		hTool::hAutoPtr<NodeData> _nodeData;//�ڵ�����
		NodeList _nodeList;//�ڵ�����

		void setAttr(const std::bitset<TaskAttrType::Max>& attr) { _attr = attr; }
		bool addNode(TaskNode* pNode);//��������ڵ�
		bool initNodeData(NodeData* pData = NULL);//��ʼ���ڵ�����

		TaskAttr(size_t weight, size_t thrdExpect, const std::bitset<TaskAttrType::Max>& attr);
	};
	//����״̬(����ʱ����)
	struct TaskStat
	{
		DefLog_Init();
		TaskStatType _state = TaskStatType::Max;//��ǰ״̬
		std::list<Task*>::iterator _stateIt;//ָ��ǰ״̬�ĵ�����

		//TaskMgr* pMgr = NULL;//ָ���Լ����ڹ�����
		//ThrdList thrds;//��ǰ���и�������߳�
		NodeListIt _nodeIt;//ָ��ǰ�����нڵ�

		~TaskStat() {}//��Ҫʵ������
	};

	class Task : public hTool::hUniqueMapVal<size_t, Task>
	{
		DefLog_Init();
		size_t _thisId = 0;//����Ψһid

		hTool::hAutoPtr<TaskAttr> _attrb;
		hTool::hAutoPtr<TaskStat> _state;
	public:
		Task(size_t weight, size_t thrdExpect, uint16_t attr);
		Task(hTool::hAutoPtr<TaskAttr> attr);
		Task(Task&& t);

		bool init(/*TaskMgr* pMgr*/);

		/*
		��������
		*/

		//��������ڵ�
		bool addNode(TaskNode* pNode) { return _attrb && _attrb->addNode(pNode); }
		//��ʼ���ڵ�����
		bool initNodeData(NodeData* pData = NULL) { return _attrb && _attrb->initNodeData(pData); }

		bool setStat(TaskStatType state);

		size_t getId() const { return _thisId; }
		size_t getWeight() const;
		hTool::hAutoPtr<TaskAttr>& getAttr() { return _attrb; }
		hTool::hAutoPtr<TaskStat>& getStat() { return _state; }

		PTaskNode getNextNode();
		//����̵߳�����,��δ����
		//void addThrd(ThreadMem* pMem);
		//����ʵ��ʹ�õ��߳���
		//size_t runTask(const size_t& rate);

	private:
		bool check() const;//һ���Լ��
	};

}
DefLog(hThread::TaskAttr, _weight, _thrdExpect, _incId, _attr, _nodeData, _nodeList);
DefLog(hThread::TaskStat, _state, _stateIt, _nodeIt);
DefLog(hThread::Task, _thisId, _attrb, _state);