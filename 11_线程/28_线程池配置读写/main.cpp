#include "global.h"
#include "hConfig.h"

BEG_ENUM(TaskMgrType)
{
	None,
	Initiative,	//���У�busyThd����ĳֵ����
	Passive,//������busyThd����ĳֵ����
}
END_ENUM(TaskMgrType, None, Initiative, Passive)

BEG_CFGSTRUCT(TreadBaseCfg)
{
	DECL_CFGSTRUCT(TreadBaseCfg);

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
	TaskMgrType t;
}
END_CFGDATA(TreadPoolCfg, base, t)


using namespace std;

int main()
{
	TreadPoolCfg t("hThread.yml");
	t.loadCfg();
	cout << t.t << endl;
	return 0;
}