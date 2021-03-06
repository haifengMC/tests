#pragma once

namespace hThread
{
	template <typename ... Args >
	void hTask::updateTaskData(size_t opt, Args ... args)
	{
		if (!check())
			return;

		_dynData->_pMgr->updateTaskData(_thisId, opt, args...);
	}
}
