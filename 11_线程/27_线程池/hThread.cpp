#include "hThread.h"

namespace hTread
{
	void hTread::TreadPool::init()
	{
		for (size_t p = TaskMgrPriority::Highest; p < TaskMgrPriority::Max; ++p)
		{
			TaskMgrBase(p, 1);
		}
	}

	void hTread::TreadPool::final()
	{
	}

	void hTread::TreadPool::run()
	{
	}

	void hTread::TreadPool::stop()
	{
	}
}

