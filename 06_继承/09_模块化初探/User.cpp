#include <map>
#include <unordered_map>
#include <iostream>

#include "UserFunc.h"
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

		funcMap[funcTy] = pFunc;
	}
}

void User::printEveryFunc()
{
	cout << "printEveryFunc:" << funcMap.size() << endl;
	for (auto pFuncPair : funcMap)
	{
		if (pFuncPair.second)
			pFuncPair.second->printMe();
	}
}
