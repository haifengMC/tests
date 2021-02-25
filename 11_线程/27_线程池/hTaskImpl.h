#pragma once

namespace hThread
{
	template <typename ... Args >
	void Task::updateTaskData(size_t opt, Args ... args)
	{
		if (!check())
			return;

		_state->_pMgr->updateTaskData(_thisId, opt, args...);
	}
}
