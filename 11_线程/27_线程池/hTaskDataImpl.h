#pragma once

namespace hThread
{
	namespace hTask
	{
		template <typename ... Args >
		void hDynamicDataMgr::updateTaskData(size_t opt, Args ... args)
		{
			if (!check())
				return;

			_pMgr->updateTaskData(_thisId, opt, args...);
		}
	}
}

