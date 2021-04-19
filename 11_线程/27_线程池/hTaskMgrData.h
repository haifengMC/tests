#pragma once

namespace hThread
{
	namespace hTaskMgr
	{
		//��������
		class hCfgData : public hDataBase
		{
			PWhTaskMgr _pMgr;//ָ���Լ����ڹ�����
			const TaskMgrCfgItem& _base;
		public:
			hCfgData(PWhTaskMgr pMgr, const TaskMgrCfgItem& base);
		};

		//�����������
		class hTaskMgrData : public hTool::hUniqueIdGen<size_t, hTaskBase>, public hDataBase
		{
			PWhTaskMgr _pMgr;//ָ���Լ����ڹ�����
		public:
			hTaskMgrData(PWhTaskMgr pMgr);
		};

		//Ȩ�ع�������
		class hWeightMgrData : public hTool::hRWeightMap<size_t>, public hDataBase
		{
			PWhTaskMgr _pMgr;//ָ���Լ����ڹ�����
		public:
			void pushTask(size_t weight, size_t tskId);
			void pushTask(PWhTask pTask);

			hWeightMgrData(PWhTaskMgr pMgr);
		};

		//״̬��������
		class hStatMgrData : public hDataBase
		{
			PWhTaskMgr _pMgr;//ָ���Լ����ڹ�����
			std::list<size_t> _states[TaskStatType::Max];//״̬����<thisId>
			std::map<size_t, TaskStatType> _stateMap;//״̬map<thisId state>
		public:
			std::list<size_t>* getStateList(TaskStatType state);
			bool updateState(size_t tskId, std::list<size_t>::iterator& statIt,
				TaskStatType oldStat, TaskStatType newStat);

			hStatMgrData(PWhTaskMgr pMgr);
		};

		//���¹�������
		class hUpdateMgrData : public hDataBase
		{
			PWhTaskMgr _pMgr;//ָ���Լ����ڹ�����
			size_t _updateId = 0;//���ݸ��� ����id
		public:
			hUpdateMgrData(PWhTaskMgr pMgr);
		};
	}
}
