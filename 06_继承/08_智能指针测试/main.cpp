#include "global.h"
#include "hTool.h"

using namespace std;

class hObject;
typedef hTool::hAutoPtr<hObject> hPObj;
typedef std::list<hPObj> hPObjList;
typedef hPObjList::iterator hPObjListIt;
typedef hTool::hWeakPtr<hObject> hPWObj;
struct hObject : public hTool::hAutoPtrObj 
{
	hPWObj _parent;
	hPObjListIt _thisIt;//对象在父类中的迭代器
	hPObjList _children;

	hObject(hObject* pObj = NULL)
	{
		if (!pObj)
			return;

		_parent = pObj->getThis<hObject>();
		_thisIt = pObj->insertChild(this);
	}
	virtual ~hObject() {} 
	virtual void Initialize() {}
	virtual void Finalize(void)
	{
		_parent = NULL;
		_thisIt = hPObjListIt();
		_children.clear();
	}

	virtual hPObjListIt insertChild(hPObj obj)
	{
		if (!obj)
			return hPObjListIt();

		return _children.insert(_children.end(), obj);
	}
	virtual void removeChild(hPObj obj)
	{
		if (!obj)
			return;
		_children.erase(obj->_thisIt);
	}
};

struct hButton : public hObject
{
	hButton(hObject* pObj = NULL) : hObject(pObj)
	{

	}
	virtual ~hButton() {}
};

struct _Adaptor : public hObject 
{
	void Initialize() 
	{
		new hButton(this);
	}
};

int main()
{
	{
		hTool::hAutoPtr<_Adaptor> _adapt(new _Adaptor);
		hTool::hAutoPtr<_Adaptor>::debugMap(cout);
		_adapt->Initialize();
		hTool::hAutoPtr<_Adaptor>::debugMap(cout);
	}
	hTool::hAutoPtr<_Adaptor>::debugMap(cout);


	return 0;
}