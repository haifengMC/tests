#include "global.h"
#include "hThread.h"
#include "hThreadPoolMgr.h"

namespace hThread
{
	void ThreadMemWork::reset()
	{
		_pTask = PWTask();
		_nodeIt = NodeListIt();
		_memIt = ThrdMemWorkListIt();
		updateStat(ThreadMemStatType::Wait);
	}

	void ThreadMemWork::setFunc()
	{
		_func = [&]()
		{
			COUT_LK("memWork_" << _id << " �����߳�����...");

			std::mutex m;
			std::unique_lock<std::mutex> lk(m);

			while (!_close)
			{
				//TaskNode* pNode = NULL;
				COUT_LK("memWork_" << _id << " �����߳̽���ѭ��...");

				_runCv.wait(lk, [&]
					{
						if (_close)
							return true;

						if (!_pTask)
						{
							COUT_LK("memWork_" << _id << " �����񣬹����̹߳���...");
							return false;
						}

						bool ret = true;
						_pTask->writeLk([&]()
							{
								if (!_pTask->checkAttr(TaskAttrType::Repeat))
									return;//�����ظ�������ִ��

								if (_pTask->canRepeat())
									return;//��ǰ���ظ�����ִ��

								_pTask->freeThrdMem(_memIt);
								reset();
								ret = false;
							});

						return ret;
					});
				if (_close)
					break;

				COUT_LK("memWork_" << _id << " �����߳���������" <<
					"task_" << _pTask->getIndex() << "...");
				PTaskAttr pAttr = _pTask->getAttr();
				PTaskStat pStat = _pTask->getStat();
				auto& nodeList = pAttr->_nodeList;
				while (_nodeIt != nodeList.end())
				{
					if (TaskStatType::Error == pStat)
					{
						COUT_LK("task_" << _pTask->getIndex() << " ���񱨴�,�߳�" <<
							"memWork_" << _id << "׼������...");
						break;
					}

					TaskNode& nodeRef = **_nodeIt;
					if (!nodeRef.initProc())
					{
						COUT_LK("task_" << _pTask->getIndex() << " ����ڵ�" <<
							"node_" << nodeRef.getId() << "��ʼ��ʧ��,�߳�" <<
							"memWork_" << getId() << "׼������...");
						_pTask->writeLk([&]() {_pTask->setStat(TaskStatType::Error); });
						break;
					}

					bool preRet = false;
					_pTask->readLk([&]() { preRet = nodeRef.preProc(); });
					if (!preRet)//Ԥ����ʧ�ܣ�����������
					{
						COUT_LK("task_" << _pTask->getIndex() << " ����ڵ�" <<
							"node_" << nodeRef.getId() << "Ԥ����ʧ��,����������,�߳�" <<
							"memWork_" << getId() << "׼������...");
						nodeRef.finalProc();
						break;
					}

					_runCv.wait(lk, [&]//�ȴ�
						{
							if (_close)
								return true;

							bool canProcV = false;
							_pTask->readLk([&]() { canProcV = _nodeIt == pStat->_curNodeIt; });
							if (!canProcV)
							{
								COUT_LK("memWork_" << getId() << " " << "task_" << _pTask->getIndex() <<
									"����ȴ�ǰ�ýڵ����_curNodeIt:" << (*pStat->_curNodeIt)->getId() <<
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

					COUT_LK("memWork_" << getId() << " ����" << "task_" << _pTask->getIndex() << "�ڵ�" << nodeRef.getId() <<
						"�������...");

				}
				//�̹߳������
				_pTask->writeLk([&]()
					{
						_pTask->freeThrdMem(_memIt);
					});
				reset();
			}
			//std::this_thread::sleep_for(std::chrono::seconds(1));
			//reset();
			COUT_LK("memWork_" << _id << " �����߳�ֹͣ����...");
		};
	}

	ThreadMemWork::ThreadMemWork(size_t id) :
		ThreadMem(id)
	{
		_type = ThreadMemType::Work;
		COUT_LK("memWork_" << _id << " �����̴߳���...");
	}

	ThreadMemWork::~ThreadMemWork()
	{
		COUT_LK("memWork_" << _id << " �����߳��ͷ�...");
	}

	void ThreadMemWork::initTask(PWTask pTask, NodeListIt nodeIt, ThrdMemWorkListIt memIt)
	{
		COUT_LK("memWork_" << _id << " ��ʼ�������߳�����" <<
			"task_" << pTask->getIndex() << "...");
		_pTask = pTask;
		_nodeIt = nodeIt;
		_memIt = memIt;
		updateStat(ThreadMemStatType::Ready);
	}

	void ThreadMemWork::runTask()
	{
		COUT_LK("memWork_" << _id << " ֪ͨ�����߳���������" <<
			"task_" << _pTask->getIndex() << "...");
		if (!_pTask || !_nodeIt._Ptr || !_memIt._Ptr)
		{
			COUT_LK("[" << getStat().getName() << getId() << "]" <<
				"_pTask" << _pTask <<
				"_nodeIt" << _nodeIt._Ptr <<
				"_memIt" << _memIt._Ptr <<
				"�����ʼ���쳣...");
			return;
		}

		if (!_pTask->runTaskNode(_nodeIt))
			return;

		updateStat(ThreadMemStatType::Run);
		notify();
	}
}