#include "global.h"
#include "hThread.h"
#include "hPoolMgr.h"

namespace hThread
{
	void hMemWork::reset()
	{
		_pTask = PWhTask();
		_nodeIt = hNodeListIt();
		_memIt = hMemWorkListIt();
		updateStat(ThreadMemStatType::Wait);
	}

	void hMemWork::setFunc()
	{
		_func = [&]()
		{
			COUT_LK("memWork_" << _id << " 工作线程启动...");

			std::mutex m;
			std::unique_lock<std::mutex> lk(m);

			while (!_close)
			{
				//TaskNode* pNode = NULL;
				COUT_LK("memWork_" << _id << " 工作线程进入循环...");

				_runCv.wait(lk, [&]
					{
						if (_close)
							return true;

						if (!_pTask)
						{
							COUT_LK("memWork_" << _id << " 无任务，工作线程挂起...");
							return false;
						}

						bool ret = true;
						_pTask->writeLk([&]()
							{
								if (!_pTask->checkAttr(TaskAttrType::Repeat))
									return;//不是重复型任务执行

								if (_pTask->canRepeat())
									return;//当前可重复继续执行

								_pTask->freeThrdMem(_memIt);
								reset();
								ret = false;
							});

						return ret;
					});
				if (_close)
					break;

				COUT_LK("memWork_" << _id << " 工作线程运行任务" <<
					"task_" << _pTask->getIndex() << "...");
				PhTskStcDt pAttr = _pTask->getStc();
				PhTskDynDt pStat = _pTask->getDyn();
				auto& nodeList = pAttr->_nodeList;
				while (_nodeIt != nodeList.end())
				{
					if (TaskStatType::Error == pStat)
					{
						COUT_LK("task_" << _pTask->getIndex() << " 任务报错,线程" <<
							"memWork_" << _id << "准备重置...");
						break;
					}

					hNode& nodeRef = **_nodeIt;
					if (!nodeRef.initProc())
					{
						COUT_LK("task_" << _pTask->getIndex() << " 任务节点" <<
							"node_" << nodeRef.getId() << "初始化失败,线程" <<
							"memWork_" << getId() << "准备重置...");
						_pTask->writeLk([&]() {_pTask->setStat(TaskStatType::Error); });
						break;
					}

					bool preRet = false;
					_pTask->readLk([&]() { preRet = nodeRef.preProc(); });
					if (!preRet)//预处理失败，做后续处理
					{
						COUT_LK("task_" << _pTask->getIndex() << " 任务节点" <<
							"node_" << nodeRef.getId() << "预处理失败,做后续处理,线程" <<
							"memWork_" << getId() << "准备重置...");
						nodeRef.finalProc();
						break;
					}

					_runCv.wait(lk, [&]//等待
						{
							if (_close)
								return true;

							bool canProcV = false;
							_pTask->readLk([&]() { canProcV = _nodeIt == pStat->_curNodeIt; });
							if (!canProcV)
							{
								COUT_LK("memWork_" << getId() << " " << "task_" << _pTask->getIndex() <<
									"任务等待前置节点完成_curNodeIt:" << (*pStat->_curNodeIt)->getId() <<
									"_nodeIt:" << (*_nodeIt)->getId() << "...");
							}

							return canProcV;
						});
					if (_close)
						break;

					_pTask->writeLk([&]()
						{
							nodeRef.onProc();
							nodeRef.finalProc();
							_pTask->finishCurNode(_memIt);
							_nodeIt = _pTask->getNextNode();
						});

					COUT_LK("memWork_" << getId() << " 任务" << "task_" << _pTask->getIndex() << "节点" << nodeRef.getId() <<
						"处理完成...");

				}
				//线程工作完毕
				_pTask->writeLk([&]()
					{
						_pTask->freeThrdMem(_memIt);
					});
				reset();
			}
			//std::this_thread::sleep_for(std::chrono::seconds(1));
			//reset();
			COUT_LK("memWork_" << _id << " 工作线程停止工作...");
		};
	}

	hMemWork::hMemWork(size_t id) :
		hMem(id)
	{
		_type = ThreadMemType::Work;
		COUT_LK("memWork_" << _id << " 工作线程创建...");
	}

	hMemWork::~hMemWork()
	{
		COUT_LK("memWork_" << _id << " 工作线程释放...");
	}

	void hMemWork::initTask(PWhTask pTask, hNodeListIt nodeIt, hMemWorkListIt memIt)
	{
		COUT_LK("memWork_" << _id << " 初始化工作线程任务" <<
			"task_" << pTask->getIndex() << "...");
		_pTask = pTask;
		_nodeIt = nodeIt;
		_memIt = memIt;
		updateStat(ThreadMemStatType::Ready);
	}

	void hMemWork::runTask()
	{
		COUT_LK("memWork_" << _id << " 通知工作线程运行任务" <<
			"task_" << _pTask->getIndex() << "...");
		if (!_pTask || !_nodeIt._Ptr || !_memIt._Ptr)
		{
			COUT_LK("[" << getStat().getName() << getId() << "]" <<
				"_pTask" << _pTask <<
				"_nodeIt" << _nodeIt._Ptr <<
				"_memIt" << _memIt._Ptr <<
				"任务初始化异常...");
			return;
		}

		if (!_pTask->runTaskNode(_nodeIt))
			return;

		updateStat(ThreadMemStatType::Run);
		notify();
	}
}