#pragma once

namespace hThread
{
	template<typename T>
	void hThreadDataBase::readLk(T func)
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		rwLock.lock();
		func();
		rwLock.unlock();
	}

	template<typename T>
	void hThreadDataBase::writeLk(T func)
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		rwLock.lock();
		func();
		rwLock.unlock();
	}
}