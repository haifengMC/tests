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
			cout << "��Ч����:" << funcTy << endl;
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
	cout << "�����¼���ʼ:" << evt.first << "_" << (size_t)evt.second << endl;
	ActGrp& actGrp = evtMap[evt.first];
	auto actListIt = actGrp.lower_bound(evt.second);
	for (; actListIt != actGrp.end(); ++actListIt)
	{
		cout << "�����¼�:" << evt.first << "_" << (size_t)actListIt->first << endl;
		for (auto& act : actListIt->second)
			act();
	}
	cout << "�����¼�����:" << evt.first << "_" << (size_t)evt.second << endl;
	curEvtList.pop_front();

	return true;
}

void User::emit(size_t evt, uint8_t step)
{
	cout << "�����¼�:" << evt << "_" << (size_t)step << endl;
	curEvtList.push_back(std::make_pair(evt, step));
}
