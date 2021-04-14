#include "global.h"
#include "hThread.h"
#include "hPoolMgr.h"
#include "hPool.h"

namespace hThread
{
//#define RD_LOCK sThreadPool.readLock()
//#define RD_UNLOCK sThreadPool.readUnlock()
//#define WT_LOCK sThreadPool.writeLock()
//#define WT_UNLOCK sThreadPool.writeUnlock()

	hPool::hPool() :
		_valid(shPoolMgr), 
		_base(shPoolMgr.getBaseCfg())
	{ 
		init(); 
	}

	hPool::~hPool() 
	{
		final();
	}

	void hPool::init()
	{
		if (!_valid)//Err
			return;

		for (auto& item : shPoolMgr.getTaskMgrCfg())
			_taskMgr.emplace_back(new hTaskMgr(item.second));
		for (auto& pMgr : _taskMgr)
			pMgr->init();
		COUT_LK("��ʼ��������������...");
		_memData[ThreadMemType::Work]._type = ThreadMemType::Work;
		_memData[ThreadMemType::Mgr]._type = ThreadMemType::Mgr;
		createThrd(_base.data.initMgrThd, ThreadMemType::Mgr);
		createThrd(_base.data.initThd, ThreadMemType::Work);
		COUT_LK("��ʼ���̳߳�Ա���...");
	}

	void hPool::final()
	{
#if 0
		for (auto& pMem : memMgr)
			DEL(pMem);
#endif
		COUT_LK("�̳߳��ͷ�...");

	}

	void hPool::run()
	{
		for (auto& data : _memData)
			data.run();
	}

	void hPool::stop()
	{
		COUT_LK("�̳߳�ֹͣ��ʼ...");
		for (auto& data : _memData)
			data.stop();
		for (auto& data : _memData)
			data.join();
		COUT_LK("�̳߳�ֹͣ���...");
	}

	size_t hPool::commitTasks(PhTask& task, TaskMgrPriority priority)
	{
		if (TaskMgrPriority::Max <= priority)
			return 0;

		return _taskMgr[priority]->commitTasks(task);
	}

	PhTask hPool::readyTasks()
	{
		size_t busyThdNum = getThrdMemNum(ThreadMemType::Work, ThreadMemStatType::Run);
		for (auto pMgr : _taskMgr)
		{
			if (!pMgr)
				continue;

			PhTask pTask = pMgr->readyTasks(busyThdNum);
			if (pTask)
				return pTask;
		}

		return PhTask();
	}

	bool hPool::initTasks(PhTask pTask, size_t thrdNum)
	{
		if (!pTask || !thrdNum)
			return false;

		size_t needNum = pTask->calcNeedThrdNum(thrdNum);
		size_t initNum = 0;
		hMemData& memData = shPool.getThrdMemData(ThreadMemType::Work);
		memData.execEvery(ThreadMemStatType::Wait, 
			[&](PhMemBase pMem)
			{
				PWhMemWork pDyMem = pMem.dynamic<hWorkMem>();
				if (!pDyMem)
				{
					COUT_LK("[" <<
						pMem->getStat().getName() <<
						pMem->getId() << "]���ǹ����߳�...");
					return true;
				}

				pTask->addThrdMem(pDyMem);
				if (++initNum < needNum)
					return true;
		
				return false;
			});

		return true;
	}

	void hPool::runTasks()
	{
		hMemData& memData = shPool.getThrdMemData(ThreadMemType::Work);
		memData.execEvery(ThreadMemStatType::Ready,
			[&](PhMemBase pMem)
			{
				PWhMemWork pDyMem = pMem.dynamic<hWorkMem>();
				if (!pDyMem)
				{
					COUT_LK("[" <<
						pMem->getStat().getName() <<
						pMem->getId() << "]���ǹ����߳�...");
					return true;
				}

				pDyMem->runTask();
				return true;
			});
	}

	void hPool::createThrd(size_t num, ThreadMemType t)
	{
		//rwLock.writeLock();
		if (ThreadMemType::Max <= t)
			return;

		hMemData& data = _memData[t];
		data.init(num);

		//rwLock.writeUnlock();
	}

	size_t hPool::getThrdMemNum(ThreadMemType memTy, ThreadMemStatType statTy)
	{
		hMemData& data = _memData[memTy];
		return data._thrdId[statTy].size();
	}

	void hPool::notifyMgrThrd()
	{
		for (auto pMem : _memData[ThreadMemType::Mgr]._memArr)
			pMem->notify();
	}
#if 0
	void ThreadPool::closeThrd(const size_t& id)
	{
		rwLock.writeLock();
		memMgr[id]->close();
		rwLock.writeUnlock();
	}

	void ThreadPool::runThrd(const size_t& num)
	{
		rwLock.readLock();
		size_t needNum = readyThd.size() < num ? readyThd.size() : num;
		rwLock.readUnlock();
		//Ԥ������������Ϊ0��û�п����̲߳�����
		if (!needNum)
			return;

		//Task** pTasks = new Task*[needNum];
		//size_t begNum = 0;

		for (auto& mgr : taskMgr)
		{
			rwLock.writeLock();
			size_t canNum = mgr.readyTasks(needNum, busyThd.size());
			rwLock.writeUnlock();

			if (!canNum)
				continue;

			rwLock.readLock();
			//������Ի�ȡ�̵߳ı���
			size_t canRate = 1.5 * readyThd.size() / canNum;
			rwLock.readUnlock();
			//�����е�������
			size_t runNum = mgr.runTasks(canNum, canRate);

			if (needNum <= runNum)//���������������������µ�
				break;

			needNum -= runNum;
		}
	}

	void ThreadPool::removeThrd(const size_t& id)
	{
		rwLock.writeLock();

		DEL(memMgr[id]);
		memMgr[id] = *memMgr.rbegin();
		memMgr[id]->setId(id);
		memMgr.pop_back();
		readyThd.erase(id);

		rwLock.writeUnlock();
	}
#endif

//#undef RD_LOCK
//#undef RD_UNLOCK
//#undef WT_LOCK
//#undef WT_UNLOCK
}