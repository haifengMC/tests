#pragma once

#include "UserFuncDefine.h"

struct UserFuncBase
{
	virtual ~UserFuncBase() {}
	virtual void printMe() = 0;

	static UserFuncBase* create(size_t funcTy);
protected:
	template <size_t FuncTy>
	static UserFuncBase* factory() { return NULL; }
	static std::unordered_map<size_t, UserFuncBase* (*)()> factMap;
};
