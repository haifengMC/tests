#pragma once


namespace hThread
{
	struct hUserData : public hDataBase
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

		//�������ݣ���д��
		virtual void update(size_t opt, void* data, size_t len) {}

		operator bool() { return _needDel; }
	};

	class hNode
	{
		DefLog_Init();
	protected:
		size_t _id = 0;
		PhUserDt _data;
		typedef hNode Base;
	public:
		virtual ~hNode() {}

		void init(size_t id, PhUserDt data);

		const size_t& getId() const { return _id; }

		virtual bool initProc() { return true; }//��ʼ�����������ã������ڴ��
		virtual bool preProc() { return true; }//Ԥ�����϶��������ڵ����ݣ������¸��ڵ�����
		virtual bool onProc() { return true; }//����������д��
		virtual bool finalProc() { return true; }//

		bool handle_initProc();
		bool handle_preProc();
		bool handle_waitProc(PWhTask pTsk, hNodeListIt nodeIt);
		bool handle_onProc();
		hNodeListIt handle_succProc(PWhTask pTsk, hWorkMemListIt memIt);
		bool handle_failProc();
	};

}
DefLog(hThread::hUserData, _id, _needDel, _totalElapsed, _elapsedRecord);
DefLog(hThread::hNode, _id);
