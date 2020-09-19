#pragma once

namespace hThread
{
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

	typedef std::list<TaskNode*> NodeList;
	typedef NodeList::iterator NodeListIt;

	typedef std::list<ThreadMem*> ThrdList;
	typedef ThrdList::iterator ThrdListIt;

	//任务属性(静态数据)
	struct TaskAttr
	{
		bool loop = false;//是否是循环任务

		size_t weight = 0;//权重
		size_t thrdExpect = 0;//期待线程数

		NodeList nodeList;//节点数据

		~TaskAttr() {}//需要实现析构
	};

	//任务状态(运行时数据)
	struct TaskStat
	{
		TaskStateType state = TaskStateType::Max;//当前状态
		std::list<Task*>::iterator stateIt;//指向当前状态的迭代器

		ThrdList thrds;//当前运行该任务的线程
		NodeListIt nodeIt;//指向当前在运行节点

		~TaskStat() {}//需要实现析构
	};

	class Task : public hTool::hUniqueMapVal<size_t, Task>
	{
		size_t thisId = 0;//任务唯一id

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
		//添加线程到任务,还未启用
		void addThrd(ThreadMem* pMem);
		//返回实际使用的线程数
		size_t runTask(const size_t& rate);
	private:
		bool check();//一般性检测
	};

}