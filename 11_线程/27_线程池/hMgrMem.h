#pragma once

namespace hThread
{
	//管理线程成员
	class hMgrMem : public hMemBase
	{
	protected:
		void setFunc();
	public:
		hMgrMem(size_t id);
		~hMgrMem();
	};
}