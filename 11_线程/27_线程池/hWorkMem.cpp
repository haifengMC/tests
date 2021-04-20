#include "global.h"
#include "hThread.h"
#include "hPoolMgr.h"

namespace hThread
{
	void hWorkMem::reset()
	{
		_pTask = PWhTask();
		_nodeIt = hNodeListIt();
		_memIt = hWorkMemListIt();
		updateStat(ThreadMemStatType::Wait);
	}

	void hWorkMem::setFunc()
	{
		_func = [&]()
		{
			COUT_LK("WorkMem_" << _id << " 工作线程启动...");

			std::mutex m;
			std::unique_lock<std::mutex> lk(m);

			while (!_close)
			{
				//TaskNode* pNode = NULL;
				COUT_LK("WorkMem_" << _id << " 工作线程进入循环...");

				_runCv.wait(lk, [&]
					{
						if (_close)
							return true;

						if (!_pTask)
						{
							COUT_LK("WorkMem_" << _id << " 无任务，工作线程挂起...");
							return false;
						}

						//不是重复型任务执行
						if (!_pTask->checkAttr(TaskAttrType::Repeat))
							return true;

						//当前可重复继续执行
						if (_pTask->canRepeat())
							return true;

						_pTask->freeThrdMem(_memIt);
						reset();
						return false;
					});
				if (_close)
					break;

				COUT_LK("WorkMem_" << _id << " 工作线程运行任务" <<
					"task_" << _pTask->getIndex() << "...");
				while (_nodeIt != _pTask->getEndNodeIt())
				{
					if (_pTask->checkStat(TaskStatType::Error))
					{
						COUT_LK("task_" << _pTask->getIndex() << " 任务报错,线程" <<
							"WorkMem_" << _id << "准备重置...");
						break;
					}

					hNode& nodeRef = **_nodeIt;
					if (!nodeRef.handle_initProc())
					{
						COUT_LK("task_" << _pTask->getIndex() << " 任务节点" <<
							"node_" << nodeRef.getId() << "初始化失败,线程" <<
							"WorkMem_" << getId() << "准备重置...");
						_pTask->updateStat(TaskStatType::Error);
						break;
					}

					if (!nodeRef.handle_preProc())//预处理失败，做后续处理
					{
						COUT_LK("task_" << _pTask->getIndex() << " 任务节点" <<
							"node_" << nodeRef.getId() << "预处理失败,做后续处理,线程" <<
							"memWork_" << getId() << "准备重置...");
						nodeRef.handle_finalProc();
						break;
					}

					_runCv.wait(lk, [&]//等待
						{
							if (_close)
								return true;

							bool canProcV = _pTask->canProc(_nodeIt);
							if (!canProcV)
							{
								COUT_LK("memWork_" << getId() << " " << "task_" << _pTask->getIndex() <<
									"任务等待前置节点完成_curNodeIt:" << (*_pTask->getCurNodeIt())->getId() <<
									"_nodeIt:" << (*_nodeIt)->getId() << "...");
							}

							return canProcV;
						});
					if (_close)
						break;

					nodeRef.handle_onProc();
					nodeRef.handle_finalProc();
					_pTask->finishCurNode(_memIt);
					_nodeIt = _pTask->getNextNode();

					COUT_LK("memWork_" << getId() << " 任务" << "task_" << _pTask->getIndex() << "节点" << nodeRef.getId() <<
						"处理完成...");

				}
				//线程工作完毕
				_pTask->freeThrdMem(_memIt);
				reset();
			}
			//std::this_thread::sleep_for(std::chrono::seconds(1));
			//reset();
			COUT_LK("memWork_" << _id << " 工作线程停止工作...");
		};
	}

	hWorkMem::hWorkMem(size_t id) :
		hMemBase(id)
	{
		_type = ThreadMemType::Work;
		COUT_LK("memWork_" << _id << " 工作线程创建...");
	}

	hWorkMem::~hWorkMem()
	{
		COUT_LK("memWork_" << _id << " 工作线程释放...");
	}

	void hWorkMem::notifyNext(hWorkMemListIt beg, hWorkMemListIt end)
	{
		if (!_memIt._Ptr)
			return;

		if (_memIt == end)
			return;

		hWorkMemListIt nextIt = std::next(memIt);
		if (nextIt == end)
			nextIt = beg;

		if (nextIt != _memIt && nextIt != end)
			(*nextIt)->notify();
	}

	void hWorkMem::initTask(PWhTask pTask, hNodeListIt nodeIt, hWorkMemListIt memIt)
	{
		COUT_LK("memWork_" << _id << " 初始化工作线程任务" <<
			"task_" << pTask->getIndex() << "...");
		_pTask = pTask;
		_nodeIt = nodeIt;
		_memIt = memIt;
		updateStat(ThreadMemStatType::Ready);
	}

	void hWorkMem::runTask()
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