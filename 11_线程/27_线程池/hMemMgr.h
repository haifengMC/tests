#pragma once

namespace hThread
{
	//管理线程成员
	class hMemMgr : public hMem
	{
	protected:
		void setFunc();
	public:
		hMemMgr(size_t id);
		~hMemMgr();
	};
}