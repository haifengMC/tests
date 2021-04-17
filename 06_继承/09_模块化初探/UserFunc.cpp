#include <iostream>
#include <unordered_map>
#include "UserFunc.h"

using namespace std;

std::unordered_map<size_t, UserFuncBase* (*)()> UserFuncBase::factMap;

UserFuncBase* UserFuncBase::create(size_t funcTy)
{
	auto it = factMap.find(funcTy);
	if (it == factMap.end())
		return NULL;

	return (*it->second)();
}