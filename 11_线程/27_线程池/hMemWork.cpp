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
				PhTskStcDt pAttr = _pTask->getStc();
				PhTskDynDt pStat = _pTask->getDyn();
				auto& nodeList = pAttr->_nodeList;
				while (_nodeIt != nodeList.end())
				{
					if (TaskStatType::Error == pStat)
					{
						COUT_LK("task_" << _pTask->getIndex() << " ���񱨴�,�߳�" <<
							"memWork_" << _id << "׼������...");
						break;
					}

					hNode& nodeRef = **_nodeIt;
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

	hMemWork::hMemWork(size_t id) :
		hMem(id)
	{
		_type = ThreadMemType::Work;
		COUT_LK("memWork_" << _id << " �����̴߳���...");
	}

	hMemWork::~hMemWork()
	{
		COUT_LK("memWork_" << _id << " �����߳��ͷ�...");
	}

	void hMemWork::initTask(PWhTask pTask, hNodeListIt nodeIt, hMemWorkListIt memIt)
	{
		COUT_LK("memWork_" << _id << " ��ʼ�������߳�����" <<
			"task_" << pTask->getIndex() << "...");
		_pTask = pTask;
		_nodeIt = nodeIt;
		_memIt = memIt;
		updateStat(ThreadMemStatType::Ready);
	}

	void hMemWork::runTask()
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