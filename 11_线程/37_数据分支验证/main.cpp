#include "global.h"
#include "hTool.h"

using namespace std;

class hTaskMgrBase;
class hUpdateMgrData
{
	hTool::hWeakPtr<hTaskMgrBase> _pMgr;//指向自己所在管理器
public:
	hUpdateMgrData(hTool::hWeakPtr<hTaskMgrBase> pMgr) : _pMgr(pMgr) {}
	void printUpdate() { cout << _pMgr << endl; }
};

class hTaskMgrBase : public hTool::hAutoPtrObj
{
	hTool::hAutoPtr <hUpdateMgrData> _update;
public:
	void init()
	{
		_update.emplace(getThis<hTaskMgrBase>());

	}

	void printMe() { cout << getThis<hTaskMgrBase>() << endl; }
	void printUpdate() { _update->printUpdate(); }
};


int main()
{
	hTool::hAutoPtr<hTaskMgrBase> pMgr;
	pMgr.emplace();
	pMgr->init();
	pMgr->printMe();
	pMgr->printUpdate();

	return 0;
}