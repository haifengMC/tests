#pragma once

namespace hThread
{
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
	
	//��������(��̬����)
	struct TaskAttr
	{
		DefLog_Init();
		size_t _weight = 0;//Ȩ��
		size_t _thrdExpect = 0;//�ڴ��߳���

		size_t _incId = 0;//�ڵ����id
		std::bitset<TaskAttrType::Max> _attr;//�������ԣ���Ӧ TaskAttrType
		PNodeData _nodeData;//�ڵ�����
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
		TaskStatType _stateTy = TaskStatType::Max;//��ǰ״̬
		std::list<size_t>::iterator _stateIt;//ָ��ǰ״̬�ĵ�����

		PWTaskMgr _pMgr;//ָ���Լ����ڹ�����
		ThrdMemWorkList _thrds;//��ǰ���и�����Ĺ����߳�
		NodeListIt 
			_curNodeIt,//ָ��ǰ�����нڵ�
			_nodeIt;//ָ����������̵߳Ľڵ�
		std::mutex rwLock;//��������ʱ�û���������

		//����״̬����
		void resetData() { _curNodeIt = _nodeIt = NodeListIt(); }
		~TaskStat() {}//��Ҫʵ������
	};

	class Task : public hTool::hAutoPtrObj, public hTool::hUniqueMapVal<size_t, Task>
	{
		DefLog_Init();
		size_t _thisId = 0;//����Ψһid

		PTaskAttr _attrb;
		PTaskStat _state;
	public:
		virtual bool canRepeat() { return false; }

		Task(size_t weight, size_t thrdExpect, uint16_t attr = 0);
		Task(PTaskAttr attr);
		Task(Task&& t);

		bool init(PWTaskMgr pMgr);

		size_t getId() const { return _thisId; }
		size_t getWeight() const;
		PTaskAttr getAttr() { return _attrb; }
		PTaskStat getStat() { return _state; }
		NodeListIt getNextNode();

		bool checkAttr(TaskAttrType attr);
		/*
		��������
		*/
		//��������ڵ�
		bool addNode(TaskNode* pNode) { return _attrb && _attrb->addNode(pNode); }
		//��ʼ���ڵ�����
		bool initNodeData(NodeData* pData = NULL) { return _attrb && _attrb->initNodeData(pData); }

		/*
		����״̬
		*/
		bool setStat(TaskStatType state);
		bool updateStat(TaskStatType state);
		bool resetStatData();
		//����̵߳�����,��δ����
		bool addThrdMem(PWThrdMemWork pMem);
		//�߳�������������ڵ�
		bool runTaskNode(NodeListIt nodeIt);
		//��ɵ�ǰ�ڵ㣬֪ͨ��һ���߳�
		void finishCurNode(ThrdMemWorkListIt memIt);
		//����ڵ��������ͷ��߳�
		void freeThrdMem(ThrdMemWorkListIt memIt);
		//���ݵ�ǰ�߳���curThrd�������߳���_thrdExpectȷ��������Ҫ���߳���
		size_t calcNeedThrdNum(size_t curThrd);
		//������������
		template <typename ... Args >
		void updateTaskData(size_t opt, Args ... args);

		template<typename T>
		void readLk(T func);
		template<typename T>
		void writeLk(T func);
	protected:
		bool check() const;//һ���Լ��
		void checkErrOut() const;
	};

}
DefLog(hThread::TaskAttr, _weight, _thrdExpect, _incId, _attr, _nodeData, _nodeList);
DefLog(hThread::TaskStat, _stateTy, _stateIt, _pMgr, _thrds, _curNodeIt, _nodeIt);
DefLog(hThread::Task, _thisId, _attrb, _state);