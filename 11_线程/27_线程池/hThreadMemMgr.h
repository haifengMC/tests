#pragma once

namespace hThread
{
	//�����̳߳�Ա
	class ThreadMemMgr : public ThreadMem
	{
	protected:
		void setFunc();
	public:
		ThreadMemMgr(size_t id);
		~ThreadMemMgr();
	};
}