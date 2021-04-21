#pragma once

namespace hThread
{
	namespace hTask
	{
		template <typename T>
		hTool::hWeakPtr<T> hStatic::hNodeData::getUserData()
		{
			hTool::hWeakPtr<T> pData;
			readLk([&]() { pData = _nodeData.dynamic<T>(); });
			return pData;
		}
	}

	template <typename T>
	hTool::hWeakPtr<T> hTaskBase::getUserData()
	{
		if (_stcData)
			return hTool::hWeakPtr<T>();
		
		return _stcData->getUserData<T>();
	}

	template <typename ... Args >
	void hTaskBase::updateTaskData(size_t opt, Args ... args)
	{
		if (!check())
			return;

		_dynData->updateTaskData(_thisId, opt, args...);
	}
}
