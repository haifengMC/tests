#pragma once


namespace hThread
{
	struct NodeData
	{
	protected:
		typedef NodeData Base;
	public:
		size_t id = 0;
		bool needDel = false;
		uint64_t totalElapsed = 0;
		std::map<size_t, uint64_t> elapsedRecord;//id-time

		NodeData() {}
		NodeData(const size_t& id) : id(id) {}
		virtual ~NodeData() {}

		operator bool() { return needDel; }

		virtual std::ostream& debugShow(std::ostream& os, uint8_t n = 0, char c = '\t');
	};

	class TaskNode
	{
	protected:
		size_t _id = 0;
		hTool::hAutoPtr<NodeData> _data;
		typedef TaskNode Base;
	public:
		virtual ~TaskNode() {}

		void init(size_t id, hTool::hAutoPtr<NodeData> _data);
		const size_t& getId() const { return _id; }

		virtual bool canProc(size_t id) { return _id == id; }
		virtual bool initProc() { return true; }//初始化处理，读配置，分配内存等
		virtual bool preProc() { return true; }//预处理，上读锁，检测节点数据，设置下个节点数据
		virtual bool onProc() { return true; }//处理函数，上写锁
		virtual bool finalProc() { return true; }//

		virtual std::ostream& debugShow(std::ostream& os, uint8_t n = 0, char c = '\t');
	};

}
DefLog(hThread::NodeData, id, needDel, totalElapsed, elapsedRecord);