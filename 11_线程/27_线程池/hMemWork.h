#pragma once

namespace hThread
{
	//�����̳߳�Ա
	class hMemWork : public hMem
	{
		PWhTask _pTask;//ָ��ǰִ������
		hNodeListIt _nodeIt;//ָ���߳����еĽڵ�
		hMemWorkListIt _memIt;//�����߳��������Լ��ĵ�����
		hRWLock* _pRwLock;//������(���̳߳��ṩ)
	protected:
		void reset();
		void setFunc();
	public:
		hMemWork(size_t id);
		~hMemWork();

		void initTask(PWhTask pTask, hNodeListIt nodeIt, hMemWorkListIt memIt);
		void runTask();

	};
}