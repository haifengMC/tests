#pragma once

namespace hThread
{
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
	
	//任务静态数据(属性、节点静态数据)
	struct TaskStaticData
	{
		DefLog_Init();
		size_t _weight = 0;//权重
		size_t _thrdExpect = 0;//期待线程数

		size_t _incId = 0;//节点递增id
		std::bitset<TaskAttrType::Max> _attr;//任务属性，对应 TaskAttrType
		PNodeData _nodeData;//节点数据
		NodeList _nodeList;//节点链表

		void setAttr(const std::bitset<TaskAttrType::Max>& attr) { _attr = attr; }
		bool addNode(TaskNode* pNode);//增加任务节点
		bool initNodeData(NodeData* pData = NULL);//初始化节点数据

		TaskStaticData(size_t weight, size_t thrdExpect, const std::bitset<TaskAttrType::Max>& attr);
	};
	//任务状态(运行时数据)
	struct TaskDynamicData
	{
		DefLog_Init();
		TaskStatType _stateTy = TaskStatType::Max;//当前状态
		std::list<size_t>::iterator _stateIt;//指向当前状态的迭代器

		PWTaskMgr _pMgr;//指向自己所在管理器
		ThrdMemWorkList _thrds;//当前运行该任务的工作线程
		NodeListIt 
			_curNodeIt,//指向当前在运行节点
			_nodeIt;//指向最后载入线程的节点

		//重置状态数据
		void resetData() { _curNodeIt = _nodeIt = NodeListIt(); }
		~TaskDynamicData() {}//需要实现析构
	};

	class Task : public hThreadDataBase,  public hTool::hAutoPtrObj, public hTool::hUniqueMapVal<size_t, Task>
	{
		DefLog_Init();
		size_t _thisId = 0;//任务唯一id

		PTaskStaticData _attrb;
		PTaskDynamicData _state;
	public:
		virtual bool canRepeat() { return false; }

		Task(size_t weight, size_t thrdExpect, uint16_t attr = 0);
		Task(PTaskStaticData attr);
		Task(Task&& t);

		bool init(PWTaskMgr pMgr);

		size_t getId() const { return _thisId; }
		size_t getWeight() const;
		PTaskStaticData getAttr() { return _attrb; }
		PTaskDynamicData getStat() { return _state; }
		NodeListIt getNextNode();

		bool checkAttr(TaskAttrType attr);
		bool checkStat(TaskStatType stat);
		/*
		设置属性
		*/
		//增加任务节点
		bool addNode(TaskNode* pNode) { return _attrb && _attrb->addNode(pNode); }
		//初始化节点数据
		bool initNodeData(NodeData* pData = NULL) { return _attrb && _attrb->initNodeData(pData); }

		/*
		设置状态
		*/
		bool setStat(TaskStatType state);
		bool updateStat(TaskStatType state);
		bool resetStatData();
		//添加线程到任务,还未启用
		bool addThrdMem(PWThrdMemWork pMem);
		//线程请求运行任务节点
		bool runTaskNode(NodeListIt nodeIt);
		//完成当前节点，通知下一个线程
		void finishCurNode(ThrdMemWorkListIt memIt);
		//任务节点分配完成释放线程
		void freeThrdMem(ThrdMemWorkListIt memIt);
		//根据当前线程数curThrd和期望线程数_thrdExpect确定最终需要的线程数
		size_t calcNeedThrdNum(size_t curThrd);
		//更新任务数据
		template <typename ... Args >
		void updateTaskData(size_t opt, Args ... args);
	protected:
		bool check() const;//一般性检测
		void checkErrOut() const;
	};

}
DefLog(hThread::TaskStaticData, _weight, _thrdExpect, _incId, _attr, _nodeData, _nodeList);
DefLog(hThread::TaskDynamicData, _stateTy, _stateIt, _pMgr, _thrds, _curNodeIt, _nodeIt);
DefLog(hThread::Task, _thisId, _attrb, _state);