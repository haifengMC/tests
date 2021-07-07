#include <iostream>
#include <map>
#include <unordered_map>
#include <functional>

#include "User.h"
#include "UserFunc.h"

using namespace std;

void UserFuncBase::emit(size_t evt)
{
	pOwner->curEvtList.push_back(std::make_pair(evt, 0));
}

void UserFuncBase::conn(size_t evt, std::function<void()> act, uint8_t step)
{
	pOwner->evtMap[evt][step].push_back(act);
}

UserFuncBase* UserFuncBase::create(size_t funcTy)
{
	auto it = factMap.find(funcTy);
	if (it == factMap.end())
		return NULL;

	return (*it->second)();
}

std::unordered_map<size_t, UserFuncBase* (*)()> UserFuncBase::factMap;
