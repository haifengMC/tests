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
		virtual bool initProc() { return true; }//��ʼ�����������ã������ڴ��
		virtual bool preProc() { return true; }//Ԥ�����϶��������ڵ����ݣ������¸��ڵ�����
		virtual bool onProc() { return true; }//����������д��
		virtual bool finalProc() { return true; }//
	};
}