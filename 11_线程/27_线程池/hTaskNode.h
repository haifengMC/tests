#pragma once


namespace hThread
{
	struct NodeData
	{
		DefLog_Init();
	protected:
		typedef NodeData Base;
	public:
		size_t _id = 0;
		bool _needDel = false;
		uint64_t _totalElapsed = 0;
		std::map<size_t, uint64_t> _elapsedRecord;//id-time

		NodeData() {}
		NodeData(const size_t& id) : _id(id) {}
		virtual ~NodeData() {}

		operator bool() { return _needDel; }
	};

	class TaskNode
	{
		DefLog_Init();
	protected:
		size_t _id = 0;
		PNodeData _data;
		typedef TaskNode Base;
	public:
		virtual ~TaskNode() {}

		void init(size_t id, PNodeData _data);

		const size_t& getId() const { return _id; }

		virtual bool canProc(size_t id) { return _id == id; }
		virtual bool initProc() { return true; }//初始化处理，读配置，分配内存等
		virtual bool preProc() { return true; }//预处理，上读锁，检测节点数据，设置下个节点数据
		virtual bool onProc() { return true; }//处理函数，上写锁
		virtual bool finalProc() { return true; }//
		
	};

}
DefLog(hThread::NodeData, _id, _needDel, _totalElapsed, _elapsedRecord);
DefLog(hThread::TaskNode, _id);
