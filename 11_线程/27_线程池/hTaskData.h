#pragma once

namespace hThread
{
	namespace hTask
	{
		//����̬���ݹ���(���ԡ��ڵ㾲̬����)
		class hStaticDataMgr
		{
			DefLog_Init();
			hStatic::hAttrData _attrData;
			hStatic::hNodeData _nodeData;

		public:
			size_t getWeight() const { return _attrData.getWeight(); }
			void setAttr(const std::bitset<TaskAttrType::Max>& attr) { _attrData.setAttr(attr); }
			bool checkAttr(TaskAttrType attr) const { return _attrData.checkAttr(attr); }
			//��������ڵ�
			bool addNode(hNode* pNode) { return _nodeData.addNode(pNode); }
			//��ʼ���ڵ�����
			bool initNodeData(hStatic::hNodeData* pData = NULL) { return _nodeData.initNodeData(pData); }
			hNodeListIt getBegNodeIt() { return _nodeData.getBegNodeIt(); }
			hNodeListIt getEndNodeIt() { return _nodeData.getEndNodeIt(); }

			hStaticDataMgr(size_t weight, size_t thrdExpect, const std::bitset<TaskAttrType::Max>& attr);
		};

		//����̬���ݹ���(״̬����������)
		class hDynamicDataMgr
		{
			DefLog_Init();
			PWhTask _pTask;	//ָ���Լ���������
			PWhTaskMgr _pMgr;//ָ���Լ����ڹ�����

			hDynamic::hStatData _state;//����״̬����
			hDynamic::hRunData _run;//������������

		public:
			const char* getStatName() const { return _state.getStatName(); }
			//����״̬
			void setStat(TaskStatType stat) { _state.setStat(stat); }
			//���״̬
			bool checkStat(TaskStatType stat) const { return _state.checkStat(stat); }
			bool updateStat(TaskStatType stat) { return _state.updateStat(stat); }
			//����״̬����
			void resetData() { _run.resetData(); }
			//��ȡ��һ���ڵ�
			hNodeListIt getNextNodeIt(hNodeListIt beg, hNodeListIt end);

			hDynamicDataMgr(PWhTaskMgr pMgr, PWhTask pTask);
		};

		namespace hStatic
		{
			//��������
			struct hAttrData : public hDataBase
			{
				size_t _weight = 0;//Ȩ��
				size_t _thrdExpect = 0;//�ڴ��߳���
				std::bitset<TaskAttrType::Max> _attr;//�������ԣ���Ӧ TaskAttrType

				size_t getWeight() const;
				void setAttr(const std::bitset<TaskAttrType::Max>& attr);
				bool checkAttr(TaskAttrType attr) const;
			};

			//��̬�ڵ�����
			struct hNodeData : public hDataBase
			{
				size_t _incId = 0;//�ڵ����id

				PhUserData _nodeData;//�ڵ�����
				hNodeList _nodeList;//�ڵ�����

				bool addNode(hNode* pNode);//��������ڵ�
				bool initNodeData(hUserData* pData);

				hNodeListIt getBegNodeIt();
				hNodeListIt getEndNodeIt();
			};
		}

		namespace hDynamic
		{
			//����״̬����
			struct hStatData : public hDataBase
			{
				PWhTask _pTask;	//ָ���Լ���������
				PWhTaskMgr _pMgr;//ָ���Լ����ڹ�����

				TaskStatType _stateTy = TaskStatType::Max;//��ǰ״̬
				std::list<size_t>::iterator _stateIt;//ָ��ǰ״̬�ĵ�����

				const char* getStatName() const;
				void setStat(TaskStatType stat);
				bool updateStat(TaskStatType stat);
				bool checkStat(TaskStatType stat)  const;

				hStatData(PWhTaskMgr pMgr, PWhTask pTask);
			};

			//������������
			struct hRunData :public hDataBase
			{
				PWhTask _pTask;	//ָ���Լ���������
				PWhTaskMgr _pMgr;//ָ���Լ����ڹ�����

				hMemWorkList _thrds;//��ǰ���и�����Ĺ����߳�
				hNodeListIt
					_curNodeIt,//ָ��ǰ�����нڵ�
					_nodeIt;//ָ����������̵߳Ľڵ�

				//����״̬����
				void resetData() { writeLk([&]() { _curNodeIt = _nodeIt = hNodeListIt(); }); }
				hNodeListIt getNextNodeIt(hNodeListIt beg, hNodeListIt end, bool isLoop);

				hRunData(PWhTaskMgr pMgr, PWhTask pTask);
			};
		}
	}
}
DefLog(hThread::hTaskStaticData, _weight, _thrdExpect, _incId, _attr, _nodeData, _nodeList);
DefLog(hThread::hTaskDynamicData, _stateTy, _stateIt, _pMgr, _thrds, _curNodeIt, _nodeIt);
