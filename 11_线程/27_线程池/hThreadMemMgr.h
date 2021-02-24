#pragma once

namespace hThread
{
	//管理线程成员
	class ThreadMemMgr : public ThreadMem
	{
	protected:
		void setFunc();
	public:
		ThreadMemMgr(size_t id);
		~ThreadMemMgr();
	};
}