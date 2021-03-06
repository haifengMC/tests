#pragma once

namespace hThread
{
#if 0
	class AllTasksData
	{
		std::map<size_t, TaskData> tasks;//<id-Task>

		hTool::hUniqueIdGen<size_t, TaskData> tasksIdGen;//id生成器
		hTool::hRWeightMap<TaskData*> weights;//权重管理
		std::list<TaskData*> states[TaskStateType::Max];//状态管理
	public:
		AllTasksData();

		//提交任务，将新任务提交给管理器，提交后默认状态为等待
		size_t commitTasks(Task** task, size_t num);
		//准备任务，按权重取出等待任务放入就绪任务，返回取出数量
		size_t readyTasks(size_t num);
		//取消已准备任务,将就绪任务放回等待状态
		void cancelReadyTasks();
		//执行任务，就绪任务，返回实际执行的任务,numThr可用线程数
		size_t runTasks(size_t numThr, size_t rate);
		size_t pushTasks(Task** const& task, const size_t& num);
		size_t popTasks(Task** const& task, const size_t& num);
	};
#endif

	class hTask : public hTool::hAutoPtrObj, public hTool::hUniqueMapVal<size_t, hTask>
	{
		DefLog_Init();
		size_t _thisId = 0;//任务唯一id

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
		设置属性
		*/
		//增加任务节点
		bool addNode(hNode* pNode) { return _stcData && _stcData->addNode(pNode); }
		//初始化节点数据
		bool initNodeData(hNodeData* pData = NULL) { return _stcData && _stcData->initNodeData(pData); }

		/*
		设置状态
		*/
		bool setStat(TaskStatType state);
		bool updateStat(TaskStatType state);
		bool resetStatData();
		//添加线程到任务,还未启用
		bool addThrdMem(PWhMemWork pMem);
		//线程请求运行任务节点
		bool runTaskNode(hNodeListIt nodeIt);
		//完成当前节点，通知下一个线程
		void finishCurNode(hMemWorkListIt memIt);
		//任务节点分配完成释放线程
		void freeThrdMem(hMemWorkListIt memIt);
		//根据当前线程数curThrd和期望线程数_thrdExpect确定最终需要的线程数
		size_t calcNeedThrdNum(size_t curThrd);
		//更新任务数据
		template <typename ... Args >
		void updateTaskData(size_t opt, Args ... args);
	protected:
		bool check() const;//一般性检测
		void checkErrOut() const;
	};

}
DefLog(hThread::hTask, _thisId, _stcData, _dynData);