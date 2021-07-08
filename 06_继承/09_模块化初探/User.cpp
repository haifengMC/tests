#include "global.h"
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

bool User::checkCurEvtList() const
{
	return !curEvtList.empty();
}

bool User::doCurEvtList()
{
	if (curEvtList.empty())
		return false;

	auto& evt = curEvtList.front();
	cout << "处理事件开始:" << evt.first << "_" << (size_t)evt.second << endl;
	ActGrp& actGrp = evtMap[evt.first];
	auto actListIt = actGrp.lower_bound(evt.second);
	for (; actListIt != actGrp.end(); ++actListIt)
	{
		cout << "处理事件:" << evt.first << "_" << (size_t)actListIt->first << endl;
		for (auto& act : actListIt->second)
			act();
	}
	cout << "处理事件结束:" << evt.first << "_" << (size_t)evt.second << endl;
	curEvtList.pop_front();

	return true;
}

void User::emit(size_t evt, uint8_t step)
{
	cout << "触发事件:" << evt << "_" << (size_t)step << endl;
	curEvtList.push_back(std::make_pair(evt, step));
}
