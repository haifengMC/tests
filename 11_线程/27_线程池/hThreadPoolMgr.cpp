#include "global.h"
#include "hThread.h"
#include "hThreadPoolMgr.h"

namespace hThread
{
	ThreadPoolMgr::ThreadPoolMgr() : _invalid(false), 
		cfgData("hThread.yml")
	{
		if (!cfgData.loadCfg())
		{//Err
			_invalid = true;
			return;
		}
	}
}