#pragma once

namespace hThread
{
	//工作线程成员
	class ThreadMemWork : public ThreadMem
	{
		PWTask _pTask;//指向当前执行任务
		NodeListIt _nodeIt;//指向本线程运行的节点
		ThrdMemWorkListIt _memIt;//任务线程链表中自己的迭代器
		hRWLock* _pRwLock;//任务锁(由线程池提供)
	protected:
		void reset();
		void setFunc();
	public:
		ThreadMemWork(size_t id);
		~ThreadMemWork();

		void initTask(PWTask pTask, NodeListIt nodeIt, ThrdMemWorkListIt memIt);
		void runTask();

	};
}