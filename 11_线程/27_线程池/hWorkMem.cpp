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
			COUT_LK("WorkMem_" << _id << " �����߳�����...");

			std::mutex m;
			std::unique_lock<std::mutex> lk(m);

			while (!_close)
			{
				//TaskNode* pNode = NULL;
				COUT_LK("WorkMem_" << _id << " �����߳̽���ѭ��...");

				_runCv.wait(lk, [&]
					{
						if (_close)
							return true;

						if (!_pTask)
						{
							COUT_LK("WorkMem_" << _id << " �����񣬹����̹߳���...");
							return false;
						}

						//�����ظ�������ִ��
						if (!_pTask->checkAttr(TaskAttrType::Repeat))
							return true;

						//��ǰ���ظ�����ִ��
						if (_pTask->canRepeat())
							return true;

						_pTask->freeThrdMem(_memIt);
						reset();
						return false;
					});
				if (_close)
					break;

				COUT_LK("WorkMem_" << _id << " �����߳���������" <<
					"task_" << _pTask->getIndex() << "...");
				while (_nodeIt != _pTask->getEndNodeIt())
				{
					if (_pTask->checkStat(TaskStatType::Error))
					{
						COUT_LK("task_" << _pTask->getIndex() << " ���񱨴�,�߳�" <<
							"WorkMem_" << _id << "׼������...");
						break;
					}

					hNode& nodeRef = **_nodeIt;
					if (!nodeRef.handle_initProc())
					{
						COUT_LK("task_" << _pTask->getIndex() << " ����ڵ�" <<
							"node_" << nodeRef.getId() << "��ʼ��ʧ��,�߳�" <<
							"WorkMem_" << getId() << "׼������...");
						_pTask->updateStat(TaskStatType::Error);
						break;
					}

					if (!nodeRef.handle_preProc())//Ԥ����ʧ�ܣ�����������
					{
						COUT_LK("task_" << _pTask->getIndex() << " ����ڵ�" <<
							"node_" << nodeRef.getId() << "Ԥ����ʧ��,����������,�߳�" <<
							"memWork_" << getId() << "׼������...");
						nodeRef.handle_finalProc();
						break;
					}

					_runCv.wait(lk, [&]//�ȴ�
						{
							if (_close)
								return true;

							bool canProcV = _pTask->canProc(_nodeIt);
							if (!canProcV)
							{
								COUT_LK("memWork_" << getId() << " " << "task_" << _pTask->getIndex() <<
									"����ȴ�ǰ�ýڵ����_curNodeIt:" << (*_pTask->getCurNodeIt())->getId() <<
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

					COUT_LK("memWork_" << getId() << " ����" << "task_" << _pTask->getIndex() << "�ڵ�" << nodeRef.getId() <<
						"�������...");

				}
				//�̹߳������
				_pTask->freeThrdMem(_memIt);
				reset();
			}
			//std::this_thread::sleep_for(std::chrono::seconds(1));
			//reset();
			COUT_LK("memWork_" << _id << " �����߳�ֹͣ����...");
		};
	}

	hWorkMem::hWorkMem(size_t id) :
		hMemBase(id)
	{
		_type = ThreadMemType::Work;
		COUT_LK("memWork_" << _id << " �����̴߳���...");
	}

	hWorkMem::~hWorkMem()
	{
		COUT_LK("memWork_" << _id << " �����߳��ͷ�...");
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
		COUT_LK("memWork_" << _id << " ��ʼ�������߳�����" <<
			"task_" << pTask->getIndex() << "...");
		_pTask = pTask;
		_nodeIt = nodeIt;
		_memIt = memIt;
		updateStat(ThreadMemStatType::Ready);
	}

	void hWorkMem::runTask()
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