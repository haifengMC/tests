#pragma once

namespace hThread
{
	//�����̳߳�Ա
	class ThreadMemWork : public ThreadMem
	{
		PWTask _pTask;//ָ��ǰִ������
		NodeListIt _nodeIt;//ָ���߳����еĽڵ�
		ThrdMemWorkListIt _memIt;//�����߳��������Լ��ĵ�����
		hRWLock* _pRwLock;//������(���̳߳��ṩ)
	protected:
		void reset();
		void setFunc();
	public:
		ThreadMemWork(size_t id);
		~ThreadMemWork();

		void initTask(PWTask pTask, NodeListIt nodeIt, ThrdMemWorkListIt memIt);
		void runTask();

	};
}