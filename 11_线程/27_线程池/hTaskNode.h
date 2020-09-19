#pragma once


namespace hThread
{
	struct NodeData
	{
		size_t id = 0;
		bool needDel = false;
		uint64_t totalElapsed = 0;
		std::map<size_t, uint64_t> elapsedRecord;//id-time

		NodeData() {}
		NodeData(const size_t& id) : id(id) {}
		virtual ~NodeData() {}

		operator bool() { return needDel; }
	};

	class TaskNode
	{
		friend class Task;
	protected:
		size_t id = 0;
		NodeData* data = NULL;
	public:
		virtual ~TaskNode() {}
		const size_t& getId() const { return id; }

		virtual bool canProc(const size_t& id) { return this->id == id; }
		virtual bool initProc() { return true; }//初始化处理，读配置，分配内存等
		virtual bool preProc() { return true; }//预处理，上读锁，检测节点数据，设置下个节点数据
		virtual bool onProc() { return true; }//处理函数，上写锁
		virtual bool finalProc() { return true; }//
	};
}