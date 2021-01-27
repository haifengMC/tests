#include "global.h"
#include "hTool.h"
#include "hConfig.h"

BEG_CFGSTRUCT(ThreadBaseCfg)
{
	size_t minThd = 0;
	size_t initThd = 0;
	size_t runThd = 0;
	size_t maxThd = 0;
}
END_CFGSTRUCT(ThreadBaseCfg, minThd, initThd, runThd, maxThd)

//template <>
//struct Logger<ThreadBaseCfg>
//{
//	static std::ostream& debug(std::ostream& os, const ThreadBaseCfg& t, uint8_t n = 0, char c = '\t')
//	{
//		os << std::string(n++, c) << "[" << TO_STRING(ThreadBaseCfg) << "]";
//		return os;
//	}
//};

BEG_ENUM(TaskMgrType)
{
	None,
	Initiative,	//运行，busyThd到达某值阻塞
	Passive,//阻塞，busyThd不足某值运行
}
END_ENUM(TaskMgrType, None, Initiative, Passive)

#if 1
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
#else
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
#endif

BEG_CFGMAP(TaskMgrCfg)
{
	TaskMgrType tType = TaskMgrType::None;
	TaskMgrPriority priority = TaskMgrPriority::Max;
}
END_CFGMAP(TaskMgrCfg, TaskMgrPriority, priority, tType)

BEG_CFGDATA(ThreadPoolCfg)
{
	ThreadBaseCfg baseCfg;
	TaskMgrCfg taskMgrCfg;
}
END_CFGDATA(ThreadPoolCfg, baseCfg, taskMgrCfg)

using namespace std;

int main()
{
//#define STRUCTENUM_F(n, em, nm, va) case nm::em: va = nm::em; break
//	cout << TO_STRING(REPEAT_A_SEP(STRUCTENUM_F, 2, SEM_M, TaskMgrPriority, value, Highest, Higher)) << endl;
//#undef STRUCTENUM_F

	ThreadBaseCfg cfg;
	Debug(cout, cfg) << endl;

	TaskMgrType tType;
	Debug(cout, tType) << endl;
	Debug(cout, 1) << endl;
	Debug(cout, "hello") << endl;

	TaskMgrCfgItem item;
	Debug(cout, item) << endl;

	TaskMgrCfg mCfg;
	mCfg.insert(make_pair(TaskMgrPriority::Higher, TaskMgrCfgItem()));
	mCfg.insert(make_pair(TaskMgrPriority::Low, TaskMgrCfgItem()));
	Debug(cout, mCfg) << endl;
	
	ThreadPoolCfg t("hThread.yml");
	t.loadCfg();
	Debug(cout, t) << endl;
	cout << "------" << endl;

	vector<int>::iterator it;
	cout << it._Ptr << endl;

	//TaskMgrCfg2 c2("hThread.yml");
	//c2.loadCfg();

	return 0;
}