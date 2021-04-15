#pragma once

namespace hThread
{
	//工作线程成员
	class hWorkMem : public hMemBase
	{
		PWhTask _pTask;//指向当前执行任务
		hNodeListIt _nodeIt;//指向本线程运行的节点
		hMemWorkListIt _memIt;//任务线程链表中自己的迭代器
		hRWLock* _pRwLock;//任务锁(由线程池提供)
	protected:
		void reset();
		void setFunc();
	public:
		hWorkMem(size_t id);
		~hWorkMem();

		void notifyNext(hMemWorkListIt beg, hMemWorkListIt end);
		void initTask(PWhTask pTask, hNodeListIt nodeIt, hMemWorkListIt memIt);
		void runTask();

	};
}