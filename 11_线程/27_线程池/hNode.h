#pragma once


namespace hThread
{
	struct hNodeData
	{
		DefLog_Init();
	protected:
		typedef hNodeData Base;
	public:
		size_t _id = 0;
		bool _needDel = false;
		uint64_t _totalElapsed = 0;
		std::map<size_t, uint64_t> _elapsedRecord;//id-time

		hNodeData() {}
		hNodeData(const size_t& id) : _id(id) {}
		virtual ~hNodeData() {}

		//�������ݣ���д��
		virtual void update(size_t opt, ...) {}

		operator bool() { return _needDel; }
	};

	class hNode
	{
		DefLog_Init();
	protected:
		size_t _id = 0;
		PhNodeData _data;
		typedef hNode Base;
	public:
		virtual ~hNode() {}

		void init(size_t id, PhNodeData _data);

		const size_t& getId() const { return _id; }

		virtual bool initProc() { return true; }//��ʼ�����������ã������ڴ��
		virtual bool preProc() { return true; }//Ԥ�����϶��������ڵ����ݣ������¸��ڵ�����
		virtual bool onProc() { return true; }//����������д��
		virtual bool finalProc() { return true; }//
		
	};

}
DefLog(hThread::hNodeData, _id, _needDel, _totalElapsed, _elapsedRecord);
DefLog(hThread::hNode, _id);
