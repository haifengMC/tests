#pragma once

namespace hThread
{
	//�����̳߳�Ա
	class hMgrMem : public hMemBase
	{
	protected:
		void setFunc();
	public:
		hMgrMem(size_t id);
		~hMgrMem();
	};
}