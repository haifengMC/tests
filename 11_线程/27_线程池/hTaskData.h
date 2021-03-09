#pragma once

namespace hThread
{
	namespace hTask
	{
		struct hAttrData;//��������
		struct hStcNodeData;//��̬�ڵ�����
	}
	struct hTaskStatData;//����״̬����
	struct hTaskRunData;//������������

	//����̬����(���ԡ��ڵ㾲̬����)
	struct hTaskStaticData
	{
		DefLog_Init();

		hTask::hAttrData _attr;
		hTask::hStcNodeData _node;

		void setAttr(const std::bitset<TaskAttrType::Max>& attr) { _attr = attr; }
		bool addNode(hNode* pNode);//��������ڵ�
		bool initNodeData(hNodeData* pData = NULL);//��ʼ���ڵ�����

		hTaskStaticData(size_t weight, size_t thrdExpect, const std::bitset<TaskAttrType::Max>& attr);
	};

	//��̬����
	struct hTaskDynamicData
	{
		DefLog_Init();
		PWhTask _pTask;	//ָ���Լ���������
		PWhTaskMgr _pMgr;//ָ���Լ����ڹ�����
			
		hTaskStatData _state;//����״̬����
		hTaskRunData _run;//������������

		//���״̬
		bool checkStat(TaskStatType stat) const { return _state.checkStat(stat); }
		//����״̬����
		void resetData() { _run.resetData(); }

		hTaskDynamicData(PWhTaskMgr pMgr, PWhTask pTask);
		~hTaskDynamicData() {}//��Ҫʵ������
	};

	namespace hTask
	{
		//��������
		struct hAttrData : public hDataBase
		{
			size_t _weight = 0;//Ȩ��
			size_t _thrdExpect = 0;//�ڴ��߳���
			std::bitset<TaskAttrType::Max> _attr;//�������ԣ���Ӧ TaskAttrType
		};

		//��̬�ڵ�����
		struct hStcNodeData : public hDataBase
		{
			size_t _incId = 0;//�ڵ����id

			PhNodeData _nodeData;//�ڵ�����
			hNodeList _nodeList;//�ڵ�����
		};

	}

	//����״̬����
	struct hTaskStatData : public hDataBase
	{
		PWhTask _pTask;	//ָ���Լ���������
		PWhTaskMgr _pMgr;//ָ���Լ����ڹ�����

		TaskStatType _stateTy = TaskStatType::Max;//��ǰ״̬
		std::list<size_t>::iterator _stateIt;//ָ��ǰ״̬�ĵ�����

		bool checkStat(TaskStatType stat)  const;

		hTaskStatData(PWhTaskMgr pMgr, PWhTask pTask);
	};

	//������������
	struct hTaskRunData :public hDataBase
	{
		PWhTask _pTask;	//ָ���Լ���������
		PWhTaskMgr _pMgr;//ָ���Լ����ڹ�����

		hMemWorkList _thrds;//��ǰ���и�����Ĺ����߳�
		hNodeListIt
			_curNodeIt,//ָ��ǰ�����нڵ�
			_nodeIt;//ָ����������̵߳Ľڵ�

		//����״̬����
		void resetData() { writeLk([&]() { _curNodeIt = _nodeIt = hNodeListIt(); }); }

		hTaskRunData(PWhTaskMgr pMgr, PWhTask pTask);
	};
}
DefLog(hThread::hTaskStaticData, _weight, _thrdExpect, _incId, _attr, _nodeData, _nodeList);
DefLog(hThread::hTaskDynamicData, _stateTy, _stateIt, _pMgr, _thrds, _curNodeIt, _nodeIt);
