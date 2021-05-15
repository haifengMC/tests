#include "global.h"
//#include "hRect.h"
#include "hObjectBase.h"

hObjectBase::hObjectBase(PWhObj parent)
{
	if (!parent)
		return;

	_parent = parent;
	_thisIt = parent->insertChild(this);
}

void hObjectBase::loadUi()
{
	new hObjectBase(getThis<hObjectBase>());
}

#if 0
GLuint hObjectBase::getBufSize()
{
	GLuint size = 0;
	for (auto childIt = _children.begin(); childIt != _children.end(); ++childIt)
		size += (*childIt)->getBufSize();

	return size;
}

GLuint hObjectBase::getEleBufSize()
{
	GLuint size = 0;
	for (auto childIt = _children.begin(); childIt != _children.end(); ++childIt)
		size += (*childIt)->getEleBufSize();

	return size;
}

//void hObject::initialize(const hSize& winSize, GLuint vbo, GLuint& bOffset, GLuint veo, GLuint& eOffset)
//{
//	//for (auto childIt = _children.begin(); childIt != _children.end(); ++childIt)
//	//	(*childIt)->initialize(winSize, vbo, bOffset, veo, eOffset);
//}

void hObjectBase::display()
{
	//for (auto childIt = _children.begin(); childIt != _children.end(); ++childIt)
	//	(*childIt)->display();
}

void hObjectBase::finalize()
{
	//if (_parent)
	//{
	//	_parent->removeChild(_thisIt);
	//	_parent = NULL;
	//	_thisIt = hObjListIt();
	//}
	//
	//for (auto childIt = _children.begin(); childIt != _children.end();)
	//{
	//	auto pChild = *childIt++;
	//	pChild->finalize();
	//	delete pChild;
	//}
}

void hObjectBase::removeChild(hObjListIt objIt)
{
	//if (!objIt._Ptr)
	//	return;
	//
	//_children.erase(objIt);
}

#endif


hObjListIt hObjectBase::insertChild(hObjectBase* obj)
{
	if (!obj)
		return hObjListIt();

	return _children.insert(_children.end(), obj);
}