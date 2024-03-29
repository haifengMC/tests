#include "global.h"
#include "hThread.h"
#include "hPoolMgr.h"

namespace hThread
{
	void hMgrMem::setFunc()
	{
		_func = [&]()
		{
			COUT_LK("管理线程" << MGR_MEM(_id) << "启动...");

			std::mutex m;
			std::unique_lock<std::mutex> lk(m);

			while (!_close)
			{
				COUT_LK("管理线程" << MGR_MEM(_id) << "进入循环...");

				PhTask pTask;
				size_t thrdNum = 0;//已就绪的工作线程数
				size_t detachNum = 0;//已分离的工作线程数
				_runCv.wait(lk, [&]
					{
						if (_close)
							return true;

						thrdNum = shPool.getThrdMemNum(ThreadMemType::Work, ThreadMemStatType::Wait);
						if (!thrdNum)
						{
							COUT_LK("无可用线程，管理线程" << MGR_MEM(_id) << "挂起...");
							return false;
						}

						pTask = shPool.readyTasks();
						if (!pTask)
						{
							COUT_LK("无任务，管理线程" << MGR_MEM(_id) << "挂起...");
							return false;
						}

						return true;
					});
				if (_close)
					break;

				COUT_LK("管理线程" << MGR_MEM(_id) << "初始化任务" <<
					TSK(pTask->getIndex()) << "...");
				if (!shPool.initTasks(pTask, thrdNum))
					continue;

				COUT_LK("管理线程" << MGR_MEM(_id) << "通知工作线程执行任务" <<
					TSK(pTask->getIndex()) << "...");
				shPool.runTasks();
			}
			//std::this_thread::sleep_for(std::chrono::seconds(2));
			COUT_LK(MGR_MEM(_id) << " 管理线程停止工作...");
		};
	}

	hMgrMem::hMgrMem(size_t id) :
		hMemBase(id)
	{
		_type = ThreadMemType::Mgr;
		COUT_LK(MGR_MEM(_id) << " 管理线程创建...");
	}

	hMgrMem::~hMgrMem()
	{
		COUT_LK(MGR_MEM(_id) << " 管理线程释放...");
	}
}