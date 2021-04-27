#pragma once

namespace hThread
{
	class hTaskBase : 
		public hTool::hAutoPtrObj, 
		public hTool::hUniqueMapVal<size_t, hTaskBase>
	{
		DefLog_Init();
		size_t _thisId = 0;//����Ψһid

		hTask::PhStcDt _stcData;
		hTask::PhDynDt _dynData;

	public:
		virtual bool canRepeat() const { return false; }

		hTaskBase(size_t weight, size_t thrdExpect, uint16_t attr = 0);
		hTaskBase(hTask::PhStcDt attr);
		hTaskBase(hTaskBase&& t);

		size_t getId() const { return _thisId; }
		template <typename T = hUserData>
		hTool::hWeakPtr<T> getUserData();
		template <typename T = hUserData>
		hTool::hWeakPtr<const T> getUserData() const;
		/*
		�������
		*/
		size_t getWeight() const;
		size_t getNeedThrdNum() const;
		bool checkAttr(TaskAttrType attr) const { return _stcData->checkAttr(attr); }
		//��������ڵ�
		bool addNode(hNode* pNode) { return _stcData && _stcData->addNode(pNode); }
		//��ʼ���ڵ�����
		bool initNodeData(hUserData* pData = NULL) { return _stcData && _stcData->initNodeData(pData); }
		hNodeListIt getBegNodeIt() { return _stcData->getBegNodeIt(); }
		hNodeListIt getEndNodeIt() { return _stcData->getEndNodeIt(); }
		/*
		״̬���
		*/
		hNodeListIt getNextNode();
		hNodeListIt getCurNodeIt();
		TaskStatType getStat() const;
		std::list<size_t>::iterator getStatIt();
		bool checkStat(TaskStatType state) const;
		bool updateStat(TaskStatType state);
		void setStat(TaskStatType state);
		void setStatIt(std::list<size_t>::iterator it);
		bool resetStatData();
		bool resetEndStatData();
		//����̵߳�����,��δ����
		bool addThrdMem(PWhWorkMem pMem);
		//��ʼ����ǰ���нڵ�
		void initCurNodeIt();
		//�߳�������������ڵ�
		bool runTaskNode(hNodeListIt nodeIt);
		//��ɵ�ǰ�ڵ㣬֪ͨ��һ���߳�
		void finishCurNode(hWorkMemListIt memIt);
		//����ڵ��������ͷ��߳�
		void freeThrdMem(hWorkMemListIt memIt);
		//���ݵ�ǰ�߳���curThrd�������߳���_thrdExpectȷ��������Ҫ���߳���
		size_t calcNeedThrdNum(size_t curThrd);
		//�Ƿ��ִ��
		bool canProc(hNodeListIt it);
		//������������
		void updateTaskData(size_t opt, const void* data, size_t len);

		bool init(PWhTaskMgr pMgr);

	protected:
		bool check() const;//һ���Լ��
		void checkErrOut() const;
	};
}
DefLog(hThread::hTaskBase, _thisId, _stcData, _dynData);