#pragma once

namespace hThread
{
	namespace hTaskMgr
	{
		//��������
		class hCfgData : public hDataBase
		{
			DefLog_Init();
			PWhTaskMgr _pMgr;//ָ���Լ����ڹ�����
			const TaskMgrCfgItem& _base;
		public:
			TaskMgrPriority getId() const;
			const char* getName() const;
			size_t getMaxBusyThd() const;

			hCfgData(PWhTaskMgr pMgr, const TaskMgrCfgItem* pBase);
		};

		//�����������
		class hTaskMgrData : public hTool::hUniqueIdGen<size_t, hTaskBase>, public hDataBase
		{
			DefLog_Init();
			PWhTaskMgr _pMgr;//ָ���Լ����ڹ�����
		public:
			auto insertTask(PhTask pTask) ->
				std::pair<std::map<size_t, hTool::hAutoPtr<hTaskBase>>::iterator, bool>;
			PhTask getTask(size_t tskId);
			
			hTaskMgrData(PWhTaskMgr pMgr);
		};

		//Ȩ�ع�������
		class hWeightMgrData : public hTool::hRWeightMap<size_t>, public hDataBase
		{
			DefLog_Init();
			PWhTaskMgr _pMgr;//ָ���Լ����ڹ�����
		public:
			//�����ȡһ������
			size_t getTaskAtRand();

			void pushTask(size_t weight, size_t tskId);
			void pushTask(PhTask pTask);
			void pushTask(PWhTask pTask);

			hWeightMgrData(PWhTaskMgr pMgr);
		};

		//״̬��������
		class hStatMgrData : public hDataBase
		{
			DefLog_Init();
			PWhTaskMgr _pMgr;//ָ���Լ����ڹ�����
			std::list<size_t> _states[TaskStatType::Max];//״̬����<thisId>
			std::map<size_t, TaskStatType> _stateMap;//״̬map<thisId state>
		public:
			bool updateState(size_t tskId, std::list<size_t>::iterator statIt,
				TaskStatType oldStat, TaskStatType newStat);

			std::list<size_t>::iterator pushTask(PhTask pTask);

			hStatMgrData(PWhTaskMgr pMgr);
		};

		//���¹�������
		class hUpdateMgrData : public hDataBase
		{
			DefLog_Init();
			PWhTaskMgr _pMgr;//ָ���Լ����ڹ�����
			size_t _updateId = 0;//���ݸ��� ����id
			size_t _updateWeight = 0;//���ݸ��� Ȩ��
		public:
			void setId(size_t id);
			size_t getId() const;
			void setWeight(size_t weight);
			size_t getWeight() const;

			hUpdateMgrData(PWhTaskMgr pMgr);
		};
	}
}
DefLog(hThread::hTaskMgr::hCfgData, _pMgr, _base);
DefLog(hThread::hTaskMgr::hTaskMgrData, _pMgr, _minN, _maxN, _curN, _genRange, _keySet, _mapData);
DefLog(hThread::hTaskMgr::hWeightMgrData, _pMgr, _total, _weights);
DefLog(hThread::hTaskMgr::hStatMgrData, _pMgr, _states, _stateMap);
DefLog(hThread::hTaskMgr::hUpdateMgrData, _pMgr, _updateId);