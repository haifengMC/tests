#pragma once

namespace hThread
{
		//����̬����(���ԡ��ڵ㾲̬����)
		struct hTaskStaticData
		{
			DefLog_Init();
			size_t _weight = 0;//Ȩ��
			size_t _thrdExpect = 0;//�ڴ��߳���

			size_t _incId = 0;//�ڵ����id
			std::bitset<TaskAttrType::Max> _attr;//�������ԣ���Ӧ TaskAttrType
			PhNodeData _nodeData;//�ڵ�����
			hNodeList _nodeList;//�ڵ�����

			void setAttr(const std::bitset<TaskAttrType::Max>& attr) { _attr = attr; }
			bool addNode(hNode* pNode);//��������ڵ�
			bool initNodeData(hNodeData* pData = NULL);//��ʼ���ڵ�����

			hTaskStaticData(size_t weight, size_t thrdExpect, const std::bitset<TaskAttrType::Max>& attr);
		};

		struct hTaskStatData : public hDataBase
		{
			PWhTask _pTask;	//ָ���Լ���������
			PWhTaskMgr _pMgr;//ָ���Լ����ڹ�����

			size_t _taskId = 0;	//����id
			TaskStatType _stateTy = TaskStatType::Max;//��ǰ״̬
			std::list<size_t>::iterator _stateIt;//ָ��ǰ״̬�ĵ�����

			hTaskStatData(PWhTaskMgr pMgr, PWhTask pTask);
		};

		//����״̬(����ʱ����)
		struct hTaskDynamicData
		{
			DefLog_Init();
			PWhTask _pTask;	//ָ���Լ���������
			PWhTaskMgr _pMgr;//ָ���Լ����ڹ�����
			
			hTaskStatData _state;//����״̬����
			
			hMemWorkList _thrds;//��ǰ���и�����Ĺ����߳�
			hNodeListIt
				_curNodeIt,//ָ��ǰ�����нڵ�
				_nodeIt;//ָ����������̵߳Ľڵ�

			bool checkStat(TaskStatType stat);
			//����״̬����
			void resetData() { _curNodeIt = _nodeIt = hNodeListIt(); }
			~hTaskDynamicData() {}//��Ҫʵ������
		};
	

}
DefLog(hThread::hTaskStaticData, _weight, _thrdExpect, _incId, _attr, _nodeData, _nodeList);
DefLog(hThread::hTaskDynamicData, _stateTy, _stateIt, _pMgr, _thrds, _curNodeIt, _nodeIt);
