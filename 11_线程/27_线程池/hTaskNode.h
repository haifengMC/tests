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
		virtual bool initProc() { return true; }//��ʼ�����������ã������ڴ��
		virtual bool preProc() { return true; }//Ԥ�����϶��������ڵ����ݣ������¸��ڵ�����
		virtual bool onProc() { return true; }//����������д��
		virtual bool finalProc() { return true; }//

		virtual std::ostream& debugShow(std::ostream& os, uint8_t n = 0, char c = '\t');
	};

}
DefLog(hThread::NodeData, id, needDel, totalElapsed, elapsedRecord);