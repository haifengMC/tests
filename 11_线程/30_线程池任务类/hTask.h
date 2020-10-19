#pragma once


class Task;

//任务属性(静态数据)
struct TaskAttr
{
	bool loop = false;//是否是循环任务

	size_t weight = 0;//权重
	size_t thrdExpect = 0;//期待线程数


	~TaskAttr() {}//需要实现析构
};
//任务状态(运行时数据)
struct TaskStat
{
	size_t state = 0;//当前状态
	std::list<Task*>::iterator stateIt;//指向当前状态的迭代器

	void* pMgr = NULL;//指向自己所在管理器

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
private:
};
