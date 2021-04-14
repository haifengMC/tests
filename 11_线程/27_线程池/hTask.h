#pragma once

namespace hThread
{
	class hTaskBase : public hTool::hAutoPtrObj, public hTool::hUniqueMapVal<size_t, hTaskBase>
	{
		DefLog_Init();
		size_t _thisId = 0;//����Ψһid

		hTask::PhStcDt _stcData;
		hTask::PhDynDt _dynData;

	public:
		hTaskBase(size_t weight, size_t thrdExpect, uint16_t attr = 0);
		hTaskBase(hTask::PhStcDt attr);
		hTaskBase(hTask&& t);

		size_t getId() const { return _thisId; }
		/*
		�������
		*/
		size_t getWeight() const;
		//��������ڵ�
		bool addNode(hNode* pNode) { return _stcData && _stcData->addNode(pNode); }
		//��ʼ���ڵ�����
		bool initNodeData(hUserData* pData = NULL) { return _stcData && _stcData->initNodeData(pData); }

		/*
		״̬���
		*/
		hNodeListIt getNextNode();
		void setStat(TaskStatType state) { _dynData && _dynData->setStat(state); }
		bool updateStat(TaskStatType state);
		bool resetStatData();
		//����̵߳�����,��δ����
		bool addThrdMem(PWhMemWork pMem);
		//��ʼ����ǰ���нڵ�
		void initCurNodeIt() { _dynData && _dynData->initCurNodeIt(_stcData->getBegNodeIt()); }
		//�߳�������������ڵ�
		bool runTaskNode(hNodeListIt nodeIt);
		//��ɵ�ǰ�ڵ㣬֪ͨ��һ���߳�
		void finishCurNode(hMemWorkListIt memIt);

		bool init(PWhTaskMgr pMgr);

	private:
		bool check() const;//һ���Լ��
		void checkErrOut() const;
	};

	class hTask : public hTool::hAutoPtrObj, public hTool::hUniqueMapVal<size_t, hTask>
	{
		//����ڵ��������ͷ��߳�
		void freeThrdMem(hMemWorkListIt memIt);
		//���ݵ�ǰ�߳���curThrd�������߳���_thrdExpectȷ��������Ҫ���߳���
		size_t calcNeedThrdNum(size_t curThrd);
		//������������
		template <typename ... Args >
		void updateTaskData(size_t opt, Args ... args);
	protected:
		bool check() const;//һ���Լ��
		void checkErrOut() const;
	};

}
DefLog(hThread::hTask, _thisId, _stcData, _dynData);