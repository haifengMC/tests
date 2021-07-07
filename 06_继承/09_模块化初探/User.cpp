#include <map>
#include <functional>
#include <unordered_map>
#include <iostream>

#include "UserFunc.h"
#include "UserEvent.h"
#include "User.h"

using namespace std;

void User::loadFunc()
{
	for (size_t funcTy = UserFuncType_1; funcTy < UserFuncType_Max; ++funcTy)
	{
		UserFuncBase* pFunc = UserFuncBase::create(funcTy);
		if (!pFunc)
		{
			cout << "无效类型:" << funcTy << endl;
			continue;
		}
	
		pFunc->pOwner = this;
		funcMap[funcTy] = pFunc;
	}
}

void User::printEveryFunc()
{
	cout << "printEveryFunc:" << funcMap.size() << endl;
	for (auto& pFuncPair : funcMap)
	{
		if (pFuncPair.second)
			pFuncPair.second->printMe();
	}
}

void User::initEvents()
{
	cout << "initEvents:" << funcMap.size() << endl;
	for (auto& pFuncPair : funcMap)
	{
		if (pFuncPair.second)
			pFuncPair.second->initEvent();
	}
}

bool User::doEvents()
{
	if (curEvtList.empty())
		return false;

	size_t evt = curEvtList.front();

	return false;
}
