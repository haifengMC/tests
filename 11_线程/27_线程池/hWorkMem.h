#pragma once

namespace hThread
{
	//�����̳߳�Ա
	class hWorkMem : public hMemBase
	{
		PWhTask _pTask;//ָ��ǰִ������
		hNodeListIt _nodeIt;//ָ���߳����еĽڵ�
		hWorkMemListIt _memIt;//�����߳��������Լ��ĵ�����
		hRWLock* _pRwLock;//������(���̳߳��ṩ)
	protected:
		void reset();
		void setFunc();
	public:
		hWorkMem(size_t id);
		~hWorkMem();

		void notifyNext(hWorkMemListIt beg, hWorkMemListIt end);
		void initTask(PWhTask pTask, hNodeListIt nodeIt, hWorkMemListIt memIt);
		void runTask();

	};
}