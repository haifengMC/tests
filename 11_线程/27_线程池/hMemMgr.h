#pragma once

namespace hThread
{
	//�����̳߳�Ա
	class hMemMgr : public hMem
	{
	protected:
		void setFunc();
	public:
		hMemMgr(size_t id);
		~hMemMgr();
	};
}