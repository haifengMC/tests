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

		hTool::hUniqueIdGen<size_t, TaskData> tasksIdGen;//id生成器
		hTool::hRWeightMap<TaskData*> weights;//权重管理
		std::list<TaskData*> states[TaskStateType::Max];//状态管理
	public:
		AllTasksData();

		//提交任务，将新任务提交给管理器，提交后默认状态为等待
		size_t commitTasks(Task** task, size_t num);
		//准备任务，按权重取出等待任务放入就绪任务，返回取出数量
		size_t readyTasks(size_t num);
		//取消已准备任务,将就绪任务放回等待状态
		void cancelReadyTasks();
		//执行任务，就绪任务，返回实际执行的任务,numThr可用线程数
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
	
	//任务属性(静态数据)
	struct TaskAttr
	{
		DefLog_Init();
		size_t _weight = 0;//权重
		size_t _thrdExpect = 0;//期待线程数

		size_t _incId = 0;//节点递增id
		std::bitset<TaskAttrType::Max> _attr;//任务属性，对应 TaskAttrType
		hTool::hAutoPtr<NodeData> _nodeData;//节点数据
		NodeList _nodeList;//节点链表

		void setAttr(const std::bitset<TaskAttrType::Max>& attr) { _attr = attr; }
		bool addNode(TaskNode* pNode);//增加任务节点
		bool initNodeData(NodeData* pData = NULL);//初始化节点数据

		TaskAttr(size_t weight, size_t thrdExpect, const std::bitset<TaskAttrType::Max>& attr);
	};
	//任务状态(运行时数据)
	struct TaskStat
	{
		DefLog_Init();
		TaskStatType _state = TaskStatType::Max;//当前状态
		std::list<Task*>::iterator _stateIt;//指向当前状态的迭代器

		//TaskMgr* pMgr = NULL;//指向自己所在管理器
		//ThrdList thrds;//当前运行该任务的线程
		NodeListIt _nodeIt;//指向当前在运行节点

		~TaskStat() {}//需要实现析构
	};

	class Task : public hTool::hUniqueMapVal<size_t, Task>
	{
		DefLog_Init();
		size_t _thisId = 0;//任务唯一id

		hTool::hAutoPtr<TaskAttr> _attrb;
		hTool::hAutoPtr<TaskStat> _state;
	public:
		Task(size_t weight, size_t thrdExpect, uint16_t attr);
		Task(hTool::hAutoPtr<TaskAttr> attr);
		Task(Task&& t);

		bool init(/*TaskMgr* pMgr*/);

		/*
		设置属性
		*/

		//增加任务节点
		bool addNode(TaskNode* pNode) { return _attrb && _attrb->addNode(pNode); }
		//初始化节点数据
		bool initNodeData(NodeData* pData = NULL) { return _attrb && _attrb->initNodeData(pData); }

		bool setStat(TaskStatType state);

		size_t getId() const { return _thisId; }
		size_t getWeight() const;
		hTool::hAutoPtr<TaskAttr>& getAttr() { return _attrb; }
		hTool::hAutoPtr<TaskStat>& getStat() { return _state; }

		PTaskNode getNextNode();
		//添加线程到任务,还未启用
		//void addThrd(ThreadMem* pMem);
		//返回实际使用的线程数
		//size_t runTask(const size_t& rate);

	private:
		bool check() const;//一般性检测
	};

}
DefLog(hThread::TaskAttr, _weight, _thrdExpect, _incId, _attr, _nodeData, _nodeList);
DefLog(hThread::TaskStat, _state, _stateIt, _nodeIt);
DefLog(hThread::Task, _thisId, _attrb, _state);