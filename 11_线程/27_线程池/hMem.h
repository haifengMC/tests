#pragma once

namespace hThread
{
	hMem* createThrdMem(ThreadMemType, size_t);

	struct hMemData
	{
		ThreadMemType _type = ThreadMemType::Max;
		//所有状态的线程id
		std::list<size_t> _thrdId[ThreadMemStatType::Max];
		std::vector<PhMem> _memArr;

		void init(size_t num);
		void run();
		void stop();
		void join();

		void execEvery(ThreadMemStatType statTy, std::function<bool(PhMem)> func);
	};

	class hMem
	{
		DefLog_Init();
		PThread _pThrd;
		ThreadMemStatType _statType;
	protected:
		ThreadMemType _type = ThreadMemType::Max;

		size_t _id = 0;
		std::list<size_t>::iterator _statIt;//_thrdId中指向自己的迭代器

		std::function<void()> _func;
		//运行条件
		std::condition_variable _runCv;

		bool _close = false;//关闭标识符
	protected:
		virtual void setFunc() = 0;//设置线程每个线程成员都必须实现
	public:
		hMem(size_t id);
		virtual ~hMem() {}

		ThreadMemType getType() const { return _type; }
		ThreadMemStatType getStat() const { return _statType; }
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
DefLog(hThread::hMem, _id);