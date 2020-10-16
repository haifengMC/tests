#include "global.h"
#include "hConfig.h"

BEG_CFGSTRUCT(TreadBaseCfg)
{
	size_t minThd = 0;
	size_t initThd = 0;
	size_t runThd = 0;
	size_t maxThd = 0;
}
END_CFGSTRUCT(TreadBaseCfg, minThd, initThd, runThd, maxThd)

BEG_ENUM(TaskMgrType)
{
	None,
	Initiative,	//运行，busyThd到达某值阻塞
	Passive,//阻塞，busyThd不足某值运行
}
END_ENUM(TaskMgrType, None, Initiative, Passive)

#if 0
BEG_ENUM(TaskMgrPriority)
{
	Highest,
		Higher,
		High,
		Normal,
		Low,
		Lower,
		Lowest,
		Max
}
END_ENUM(TaskMgrPriority, Max, Highest, Higher, High, Normal, Low, Lower, Lowest)
#endif
struct TaskMgrPriority
{
	enum
	{
		Highest,
		Higher,
		High,
		Normal,
		Low,
		Lower,
		Lowest,
		Max
	} value;

	TaskMgrPriority(size_t v = Max)
	{
		switch (v)
		{
#define STRUCTENUM_F(n, em, nm) case (size_t)nm::em: value = nm::em; break
			REPEAT_A_SEP(STRUCTENUM_F, 1, SEM_M, TaskMgrPriority, Highest, Higher, High, Normal, Low, Lower, Lowest);
#undef STRUCTENUM_F
		default:
			value = TaskMgrPriority::Max;
			break;
		}
	}

	bool operator<(const TaskMgrPriority& p) const { return value < p.value; }
};
//std::ostream& operator<<(std::ostream& os, const enumName& rhs); 
template <>
struct YAML::convert<TaskMgrPriority>
{
	static Node encode(const TaskMgrPriority& rhs)
	{
		return Node((size_t)rhs.value);
	}
	static bool decode(const Node& n, TaskMgrPriority& rhs)
	{
		if (!n.IsScalar())
			return false;
		switch (n.as<size_t>())
		{
			REPEAT_A_SEP(CFGENUM_DECODE_F, 1, SEM_M, TaskMgrPriority, Highest, Higher, High, Normal, Low, Lower, Lowest, Max);
		default:
			rhs = TaskMgrPriority::Max;
			break;
		}
		return true;
	}
};

BEG_CFGMAP(TaskMgrCfg)
{
	DECL_CFGMAP(TaskMgrPriority, priority);

	TaskMgrType tType = TaskMgrType::None;
	TaskMgrPriority priority = TaskMgrPriority::Max;
}
END_CFGMAP(TaskMgrCfg, TaskMgrPriority, priority, tType)

BEG_CFGDATA(ThreadPoolCfg)
{
	DECL_CFGDATA(ThreadPoolCfg, baseCfg, taskMgrCfg);

	TreadBaseCfg baseCfg;
	TaskMgrCfg taskMgrCfg;
}
END_CFGDATA()


using namespace std;

int main()
{
	ThreadPoolCfg t("hThread.yml");
	t.loadCfg();

	//TaskMgrCfg2 c2("hThread.yml");
	//c2.loadCfg();

	return 0;
}