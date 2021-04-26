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


		template <typename T>
		hTool::hWeakPtr<const T> hStatic::hNodeData::getUserData() const
		{
			hTool::hWeakPtr<const T> pData;
			readLk([&]() { pData = _nodeData.dynamic<T>(); });
			return pData;
		}
	}

	template <typename T>
	hTool::hWeakPtr<T> hTaskBase::getUserData()
	{
		if (!_stcData)
			return hTool::hWeakPtr<T>();
		
		return _stcData->getUserData<T>();
	}
	template <typename T>
	hTool::hWeakPtr<const T> hTaskBase::getUserData() const
	{
		if (!_stcData)
			return hTool::hWeakPtr<const T>();

		return _stcData->getUserData<T>();
	}
}
