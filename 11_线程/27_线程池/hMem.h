#pragma once

namespace hThread
{
	hMemBase* createThrdMem(ThreadMemType, size_t);

	struct hMemData
	{
		ThreadMemType _type = ThreadMemType::Max;
		//����״̬���߳�id
		std::list<size_t> _thrdId[ThreadMemStatType::Max];
		std::vector<PhMemBase> _memArr;

		void init(size_t num);
		void run();
		void stop();
		void join();

		void execEvery(ThreadMemStatType statTy, std::function<bool(PhMemBase)> func);
	};

	class hMemBase
	{
		DefLog_Init();
		PThread _pThrd;
		ThreadMemStatType _statType;
	protected:
		ThreadMemType _type = ThreadMemType::Max;

		size_t _id = 0;
		std::list<size_t>::iterator _statIt;//_thrdId��ָ���Լ��ĵ�����

		std::function<void()> _func;
		//��������
		std::condition_variable _runCv;

		bool _close = false;//�رձ�ʶ��
	protected:
		virtual void setFunc() = 0;//�����߳�ÿ���̳߳�Ա������ʵ��
	public:
		hMemBase(size_t id);
		virtual ~hMemBase() {}

		ThreadMemType getType() const { return _type; }
		ThreadMemStatType getStat() const { return _statType; }
		bool checkStat(ThreadMemStatType stat) const { return stat == _statType; }
		const char* getStatName() const { return _statType.getName(); }
		size_t getId() const { return _id; }

		void run();
		void stop();
		void join();

		bool setStat(ThreadMemStatType type, std::list<size_t>::iterator& it);
		bool updateStat(ThreadMemStatType type);
		void notify() { _runCv.notify_all(); }

		bool shouldBeClosed() const { return _close; }
		void close() { _close = true; }
	};
}
DefLog(hThread::hMemData, _thrdId);
DefLog(hThread::hMemBase, _id);