#include "global.h"
#include "hTool.h"
#include "hThread.h"
#include "hPoolMgr.h"

namespace hThread
{
	namespace hTaskMgr
	{
		hCfgData::hCfgData(PWhTaskMgr pMgr, const TaskMgrCfgItem& base) :
			_pMgr(pMgr), _base(base) {}

		hTaskMgrData::hTaskMgrData(PWhTaskMgr pMgr) : 
			hTool::hUniqueIdGen<size_t, hTaskBase>(50),
			_pMgr(pMgr) { resize(10000, 99999); }

		hWeightMgrData::hWeightMgrData(PWhTaskMgr pMgr) :
			_pMgr(pMgr) {}

		hStatMgrData::hStatMgrData(PWhTaskMgr pMgr) :
			_pMgr(pMgr) {}

		hUpdateMgrData::hUpdateMgrData(PWhTaskMgr pMgr) :
			_pMgr(pMgr) {}
	}
}