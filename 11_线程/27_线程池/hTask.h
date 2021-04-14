#pragma once

namespace hThread
{
	class hTaskBase : public hTool::hAutoPtrObj, public hTool::hUniqueMapVal<size_t, hTaskBase>
	{
		DefLog_Init();
		size_t _thisId = 0;//任务唯一id

		hTask::PhStcDt _stcData;
		hTask::PhDynDt _dynData;

	public:
		hTaskBase(size_t weight, size_t thrdExpect, uint16_t attr = 0);
		hTaskBase(hTask::PhStcDt attr);
		hTaskBase(hTask&& t);

		size_t getId() const { return _thisId; }
		/*
		属性相关
		*/
		size_t getWeight() const;
		//增加任务节点
		bool addNode(hNode* pNode) { return _stcData && _stcData->addNode(pNode); }
		//初始化节点数据
		bool initNodeData(hUserData* pData = NULL) { return _stcData && _stcData->initNodeData(pData); }

		/*
		状态相关
		*/
		hNodeListIt getNextNode();
		void setStat(TaskStatType state) { _dynData && _dynData->setStat(state); }
		bool updateStat(TaskStatType state);
		bool resetStatData();
		//添加线程到任务,还未启用
		bool addThrdMem(PWhMemWork pMem);
		//初始化当前运行节点
		void initCurNodeIt() { _dynData && _dynData->initCurNodeIt(_stcData->getBegNodeIt()); }
		//线程请求运行任务节点
		bool runTaskNode(hNodeListIt nodeIt);
		//完成当前节点，通知下一个线程
		void finishCurNode(hMemWorkListIt memIt);

		bool init(PWhTaskMgr pMgr);

	private:
		bool check() const;//一般性检测
		void checkErrOut() const;
	};

	class hTask : public hTool::hAutoPtrObj, public hTool::hUniqueMapVal<size_t, hTask>
	{
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