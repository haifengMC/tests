#pragma once

namespace hThread
{
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
