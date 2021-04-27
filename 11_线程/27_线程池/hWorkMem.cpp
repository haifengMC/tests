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
			COUT_LK("工作线程" << WORK_MEM(_id) << "启动...");

			std::mutex m;
			std::unique_lock<std::mutex> lk(m);

			while (!_close)
			{
				//TaskNode* pNode = NULL;
				COUT_LK("工作线程" << WORK_MEM(_id) << "进入循环...");

				_runCv.wait(lk, [&]
					{
						if (_close)
							return true;

						if (!_pTask)
						{
							COUT_LK("无任务，工作线程" << WORK_MEM(_id) << "挂起...");
							return false;
						}

						//不是重复型任务执行
						if (!_pTask->checkAttr(TaskAttrType::Repeat))
						{
							COUT_LK(TSK(_pTask->getId()) << "不是重复型任务,由" << WORK_MEM(_id) << "执行...");
							return true;
						}

						//当前可重复继续执行
						if (_pTask->canRepeat())
						{
							COUT_LK(TSK(_pTask->getId()) << "可重复执行,由" << WORK_MEM(_id) << "执行...");
							return true;
						}

						COUT_LK(TSK(_pTask->getId()) << "不可执行,释放" << WORK_MEM(_id) << "...");

						_pTask->resetEndStatData();
						_pTask->freeThrdMem(_memIt);
						reset();
						return false;
					});
				if (_close)
					break;

				COUT_LK("工作线程" << WORK_MEM(_id) << "运行任务" <<
					TSK(_pTask->getId()) << "...");
				while (_nodeIt != _pTask->getEndNodeIt())
				{
					if (_pTask->checkStat(TaskStatType::Error))
					{
						COUT_LK(TSK(_pTask->getId()) << " 任务报错,线程" <<
							WORK_MEM(_id) << "准备重置...");
						break;
					}

					hNode& nodeRef = **_nodeIt;
					if (!nodeRef.handle_initProc())
					{
						COUT_LK(TSK(_pTask->getId()) << "任务节点" <<
							NODE(nodeRef.getId()) << "初始化失败,线程" <<
							WORK_MEM(_id) << "准备重置...");
						_pTask->updateStat(TaskStatType::Error);
						break;
					}

					if (!nodeRef.handle_preProc())//预处理失败，做后续处理
					{
						COUT_LK(TSK(_pTask->getId()) << " 任务节点" <<
							NODE(nodeRef.getId()) << "预处理失败,做后续处理,线程" <<
							WORK_MEM(_id) << "准备重置...");
						nodeRef.handle_failProc();
						break;
					}

					_runCv.wait(lk, [&]//等待
						{
							if (_close)
								return true;

							return nodeRef.handle_waitProc(_pTask, _nodeIt);
						});
					if (_close)
						break;

					nodeRef.handle_onProc();
					_nodeIt = nodeRef.handle_succProc(_pTask, _memIt);

				}
				//线程工作完毕
				_pTask->freeThrdMem(_memIt);
				reset();
			}
			//std::this_thread::sleep_for(std::chrono::seconds(1));
			//reset();
			COUT_LK("工作线程"<< WORK_MEM(_id) << "停止工作...");
		};
	}

	hWorkMem::hWorkMem(size_t id) :
		hMemBase(id)
	{
		_type = ThreadMemType::Work;
		COUT_LK("工作线程"<< WORK_MEM(_id) << "创建...");
	}

	hWorkMem::~hWorkMem()
	{
		COUT_LK("工作线程" << WORK_MEM(_id) << "释放...");
	}

	void hWorkMem::notifyNext(hWorkMemListIt beg, hWorkMemListIt end)
	{
		if (!_memIt._Ptr)
			return;

		if (_memIt == end)
			return;

		hWorkMemListIt nextIt = std::next(_memIt);
		if (nextIt == end)
			nextIt = beg;

		if (nextIt != _memIt && nextIt != end)
			(*nextIt)->notify();
	}

	void hWorkMem::initTask(PWhTask pTask, hNodeListIt nodeIt, hWorkMemListIt memIt)
	{
		COUT_LK("WorkMem_" << _id << " 初始化工作线程任务" <<
			"task_" << pTask->getIndex() << "...");
		_pTask = pTask;
		_nodeIt = nodeIt;
		_memIt = memIt;
		updateStat(ThreadMemStatType::Ready);
	}

	void hWorkMem::runTask()
	{
		COUT_LK("WorkMem_" << _id << " 通知工作线程运行任务" <<
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