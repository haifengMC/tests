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

	template<typename T>
	void Task::readLk(T func)
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		_state->rwLock.lock();
		func();
		_state->rwLock.unlock();
	}

	template<typename T>
	void Task::writeLk(T func)
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		_state->rwLock.lock();
		func();
		_state->rwLock.unlock();
	}
}
