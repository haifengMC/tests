#pragma once


namespace hThread
{
	struct NodeData
	{
		size_t id = 0;
		bool needDel = false;
		uint64_t totalElapsed = 0;
		map<size_t, uint64_t> elapsedRecord;//id-time

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
		
		virtual bool preProcess() { return true; }//预处理
		virtual bool onProcess() { return true; }//处理函数
		virtual bool afterProcess() { return true; }//
	};
}