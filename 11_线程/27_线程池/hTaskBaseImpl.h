#pragma once

namespace hThread
{
	template <typename ... Args >
	void hTaskBase::updateTaskData(size_t opt, Args ... args)
	{
		if (!check())
			return;

		_dynData->updateTaskData(_thisId, opt, args...);
	}
}
