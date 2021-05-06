#pragma once

class hObjectBase;
typedef hTool::hWeakPtr<hObjectBase> PWhObj;
typedef hTool::hAutoPtr<hObjectBase> PhObj;
typedef std::list<PhObj> hObjList;
typedef hObjList::iterator hObjListIt;

class hObjectBase : public hTool::hAutoPtrObj
{
	DefLog_Init();
	PWhObj _parent;
	hObjListIt _thisIt;//对象在父类中的迭代器
	hObjList _children;
public:
	hObjectBase(PWhObj parent);
#if 0
	virtual ~hObjectBase() {}
	virtual GLuint getBufSize();
	virtual GLuint getEleBufSize();
	//virtual void initialize(const hSize& winSize, GLuint vbo, GLuint& bOffset, GLuint veo, GLuint& eOffset);
	virtual void display();
	virtual void finalize();

	virtual void removeChild(hObjListIt objIt);
#endif
	virtual hObjListIt insertChild(hObjectBase* obj);

};
DefLog(hObjectBase, _children);
