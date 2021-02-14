#include "global.h"
#include "hTool.h"

using namespace std;

struct hObject;
typedef std::list<hObject*> hObjList;
typedef hObjList::iterator hObjListIt;

struct hObject : public hTool::hAutoPtrObj 
{
	hObject* _parent = NULL;
	hObjListIt _thisIt;//对象在父类中的迭代器
	hObjList _children;

	hObject(hObject* pObj = NULL)
	{
		if (!pObj)
			return;

		_parent = pObj;
		_thisIt = pObj->insertChild(this);
	}
	virtual ~hObject() {} 
	virtual void Initialize() {}
	virtual void Finalize()
	{
		if (_parent)
		{
			_parent->removeChild(_thisIt);
			_parent = NULL;
			_thisIt = hObjListIt();
		}
		
		;
		for (auto childIt = _children.begin(); childIt != _children.end();)
		{
			auto pChild = *childIt++;
			pChild->Finalize();
			delete pChild;
		}
	}

	virtual hObjListIt insertChild(hObject* obj)
	{
		if (!obj)
			return hObjListIt();

		return _children.insert(_children.end(), obj);
	}
	virtual void removeChild(hObjListIt objIt)
	{
		if (!objIt._Ptr)
			return;

		_children.erase(objIt);
	}
};

struct hButton : public hObject
{
	hButton(hObject* pObj = NULL) : hObject(pObj)
	{
		cout << "hButton()" << endl;
	}
	~hButton() { cout << "~hButton()" << endl; }
};

struct _Adapt : public hObject
{
	void Initialize()
	{
		new hButton(this);
	}

	~_Adapt() { cout << "~_Adapt()" << endl; }
};


int main()
{
	{
		hTool::hAutoPtr<_Adapt> _adapt(new _Adapt);
		_adapt->Initialize();
		_adapt->Finalize();
	}


	return 0;
}