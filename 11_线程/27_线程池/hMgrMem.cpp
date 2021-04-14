#include "global.h"
#include "hThread.h"
#include "hPoolMgr.h"

namespace hThread
{
	void hMgrMem::setFunc()
	{
		_func = [&]()
		{
			COUT_LK("memMgr_" << _id << " �����߳�����...");

			std::mutex m;
			std::unique_lock<std::mutex> lk(m);

			while (!_close)
			{
				COUT_LK("memMgr_" << _id << " �����߳̽���ѭ��...");

				PhTask pTask;
				size_t thrdNum = 0;//�Ѿ����Ĺ����߳���
				size_t detachNum = 0;//�ѷ���Ĺ����߳���
				_runCv.wait(lk, [&]
					{
						if (_close)
							return true;

						thrdNum = shPool.getThrdMemNum(ThreadMemType::Work, ThreadMemStatType::Wait);
						if (!thrdNum)
						{
							COUT_LK("memMgr_" << _id << " �޿����̣߳������̹߳���...");
							return false;
						}

						pTask = shPool.readyTasks();
						if (!pTask)
						{
							COUT_LK("memMgr_" << _id << " �����񣬹����̹߳���...");
							return false;
						}

						return true;
					});
				if (_close)
					break;

				COUT_LK("memMgr_" << _id << " �����̳߳�ʼ������" <<
					"task_" << pTask->getIndex() << "...");
				if (!shPool.initTasks(pTask, thrdNum))
					continue;

				COUT_LK("memMgr_" << _id << " �����߳�֪ͨ�����߳�ִ������" <<
					"task_" << pTask->getIndex() << "...");
				shPool.runTasks();
			}
			//std::this_thread::sleep_for(std::chrono::seconds(2));
			COUT_LK("memMgr_" << _id << " �����߳�ֹͣ����...");
		};
	}

	hMgrMem::hMgrMem(size_t id) :
		hMemBase(id)
	{
		_type = ThreadMemType::Mgr;
		COUT_LK("memMgr_" << _id << " �����̴߳���...");
	}

	hMgrMem::~hMgrMem()
	{
		COUT_LK("memMgr_" << _id << " �����߳��ͷ�...");
	}
}