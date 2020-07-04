#pragma once
#include "hSingleton.h"
#include "hConfig.h"
#include <vector>

namespace hTread
{
	class TaskNode
	{
		size_t id;
	};
	
	class Task
	{
		size_t id;

	};
	struct TaskMgrType
	{
		enum _Value
		{
			None,
			Initiative,	//运行，busyThd到达某值阻塞
			Passive,//阻塞，busyThd不足某值运行
		};
	};

	struct TaskMgrPriority
	{
		enum _Value
		{
			Highest,
			Higher, 
			High,
			Normal,
			Low,
			Lower,
			Lowest,
			Max
		};
	};

	struct TaskMgrBase
	{
		TaskMgrPriority::_Value priority;
		TaskMgrType::_Value type;

		TaskMgrBase() : priority(TaskMgrPriority::Max), type(TaskMgrType::None) {}
		TaskMgrBase(TaskMgrPriority::_Value priority, TaskMgrType::_Value type) : priority(priority), type(type) {}
	};

	class TaskMgr
	{
		const TaskMgrBase base;
	public:
		TaskMgr(const TaskMgrBase& base) : base(base) {}
	};

	BEG_CFGSTRUCT(TreadBaseCfg)
	{
		size_t minThd;
		size_t initThd;
		size_t runThd;
		size_t maxThd;
	}
	END_CFGSTRUCT(TreadBaseCfg, minThd, initThd, runThd, maxThd)

	BEG_CFGDATA(TreadPoolCfg)
	{
		DECL_CFGDATA(TreadPoolCfg);

		TreadBaseCfg base;
		GLuint vertLoc;
		GLuint colorLoc;
		GLfloat vertice[3][2];
		GLfloat staticColor[3];
		GLfloat colors[3][3];
	}
	END_CFGDATA(TreadPoolCfg, base, vertLoc, colorLoc, vertice, staticColor, colors)


	class TreadPool : public Singleton<TreadPool>
	{
		size_t minThd, initThd, runThd, maxThd;
		size_t busyThd;

		std::vector<TaskMgr> taskMgrs;
	public:
		void init();
		void final();
		void run();
		void stop();

	};
}
