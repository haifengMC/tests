#pragma once


namespace hThread
{
	struct hUserData
	{
		DefLog_Init();
	protected:
		typedef hUserData Base;
	public:
		size_t _id = 0;
		bool _needDel = false;
		uint64_t _totalElapsed = 0;
		std::map<size_t, uint64_t> _elapsedRecord;//id-time

		hUserData() {}
		hUserData(const size_t& id) : _id(id) {}
		virtual ~hUserData() {}

		//更新数据，上写锁
		virtual void update(size_t opt, ...) {}

		operator bool() { return _needDel; }
	};

	class hNode
	{
		DefLog_Init();
	protected:
		size_t _id = 0;
		PhUserData _data;
		typedef hNode Base;
	public:
		virtual ~hNode() {}

		void init(size_t id, PhNodeData _data);

		const size_t& getId() const { return _id; }

		virtual bool initProc() { return true; }//初始化处理，读配置，分配内存等
		virtual bool preProc() { return true; }//预处理，上读锁，检测节点数据，设置下个节点数据
		virtual bool onProc() { return true; }//处理函数，上写锁
		virtual bool finalProc() { return true; }//
		
	};

}
DefLog(hThread::hUserData, _id, _needDel, _totalElapsed, _elapsedRecord);
DefLog(hThread::hNode, _id);
