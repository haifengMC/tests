#pragma once

namespace hThread
{
#if 0
	class AllTasksData
	{
		std::map<size_t, TaskData> tasks;//<id-Task>

		hTool::hUniqueIdGen<size_t, TaskData> tasksIdGen;//id������
		hTool::hRWeightMap<TaskData*> weights;//Ȩ�ع���
		std::list<TaskData*> states[TaskStateType::Max];//״̬����
	public:
		AllTasksData();

		//�ύ���񣬽��������ύ�����������ύ��Ĭ��״̬Ϊ�ȴ�
		size_t commitTasks(Task** task, size_t num);
		//׼�����񣬰�Ȩ��ȡ���ȴ��������������񣬷���ȡ������
		size_t readyTasks(size_t num);
		//ȡ����׼������,����������Żصȴ�״̬
		void cancelReadyTasks();
		//ִ�����񣬾������񣬷���ʵ��ִ�е�����,numThr�����߳���
		size_t runTasks(size_t numThr, size_t rate);
		size_t pushTasks(Task** const& task, const size_t& num);
		size_t popTasks(Task** const& task, const size_t& num);
	};
#endif

	class hTask : public hTool::hAutoPtrObj, public hTool::hUniqueMapVal<size_t, hTask>
	{
		DefLog_Init();
		size_t _thisId = 0;//����Ψһid

		PhTskStcDt _stcData;
		PhTskDynDt _dynData;
	public:
		virtual bool canRepeat() { return false; }

		hTask(size_t weight, size_t thrdExpect, uint16_t attr = 0);
		hTask(PhTskStcDt attr);
		hTask(hTask&& t);

		bool init(PWhTaskMgr pMgr);

		size_t getId() const { return _thisId; }
		size_t getWeight() const;
		PhTskStcDt getStc() { return _stcData; }
		PhTskDynDt getDyn() { return _dynData; }
		hNodeListIt getNextNode();

		bool checkAttr(TaskAttrType attr);
		bool checkStat(TaskStatType stat);
		/*
		��������
		*/
		//��������ڵ�
		bool addNode(hNode* pNode) { return _stcData && _stcData->addNode(pNode); }
		//��ʼ���ڵ�����
		bool initNodeData(hNodeData* pData = NULL) { return _stcData && _stcData->initNodeData(pData); }

		/*
		����״̬
		*/
		bool setStat(TaskStatType state);
		bool updateStat(TaskStatType state);
		bool resetStatData();
		//����̵߳�����,��δ����
		bool addThrdMem(PWhMemWork pMem);
		//�߳�������������ڵ�
		bool runTaskNode(hNodeListIt nodeIt);
		//��ɵ�ǰ�ڵ㣬֪ͨ��һ���߳�
		void finishCurNode(hMemWorkListIt memIt);
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