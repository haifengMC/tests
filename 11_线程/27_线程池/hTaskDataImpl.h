#pragma once

namespace hThread
{
	namespace hTask
	{
		template <typename ... Args >
		void hDynamicDataMgr::updateTaskData(size_t opt, Args ... args)
		{
			_pMgr->updateTaskData(_pTask->getId(), opt, args...);
		}
	}
}

