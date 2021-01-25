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
		uint16_t _attr = 0;//任务属性，对应 TaskAttrType
		size_t _weight = 0;//权重
		size_t _thrdExpect = 0;//期待线程数

		size_t _incId = 0;//节点递增id
		hTool::hAutoPtr<NodeData> _nodeData;//节点数据
		NodeList _nodeList;//节点链表

		void setAttr(uint16_t attr = 0) { _attr = attr; }
		bool addNode(TaskNode* pNode);//增加任务节点
		bool initNodeData(NodeData* pData = NULL);//初始化节点数据

		std::ostream& debugShow(std::ostream& os, uint8_t n = 0, char c = '\t');
		TaskAttr(size_t weight, size_t thrdExpect, uint16_t attr);
	};
	//任务状态(运行时数据)
	struct TaskStat
	{
		TaskStatType state = TaskStatType::Max;//当前状态
		std::list<Task*>::iterator stateIt;//指向当前状态的迭代器

		//TaskMgr* pMgr = NULL;//指向自己所在管理器
		//ThrdList thrds;//当前运行该任务的线程
		NodeListIt nodeIt;//指向当前在运行节点

		std::ostream& debugShow(std::ostream& os, uint8_t n = 0, char c = '\t');
		~TaskStat() {}//需要实现析构
	};

	class Task : public hTool::hUniqueMapVal<size_t, Task>
	{
		size_t _thisId = 0;//任务唯一id

		hTool::hAutoPtr<TaskAttr> _attr;
		hTool::hAutoPtr<TaskStat> _stat;
	public:
		Task(size_t weight, size_t thrdExpect, uint16_t attr);
		Task(hTool::hAutoPtr<TaskAttr> attr);
		Task(Task&& t);

		bool init(/*TaskMgr* pMgr*/);

		/*
		设置属性
		*/

		//增加任务节点
		bool addNode(TaskNode* pNode) { return _attr && _attr->addNode(pNode); }
		//初始化节点数据
		bool initNodeData(NodeData* pData = NULL) { return _attr && _attr->initNodeData(pData); }

		bool setStat(TaskStatType state);

		size_t getId() const { return _thisId; }
		size_t getWeight() const;
		hTool::hAutoPtr<TaskAttr>& getAttr() { return _attr; }
		hTool::hAutoPtr<TaskStat>& getStat() { return _stat; }

		PTaskNode getNextNode();
		//添加线程到任务,还未启用
		//void addThrd(ThreadMem* pMem);
		//返回实际使用的线程数
		//size_t runTask(const size_t& rate);

		std::ostream& debugShow(std::ostream& os, uint8_t n = 0, char c = '\t');
	private:
		bool check() const;//一般性检测
	};

}