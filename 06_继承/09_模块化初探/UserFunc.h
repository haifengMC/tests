#pragma once

#include "UserFuncDefine.h"

class UserFuncBase
{
	friend class User;
protected:
	User* pOwner = NULL;
public:
	virtual ~UserFuncBase() {}
	virtual void printMe() = 0;
	virtual void initEvent() {};

	void emit(size_t evt, uint8_t step = 0);
	void conn(size_t evt, std::function<void()> act, uint8_t step = 0);

	static UserFuncBase* create(size_t funcTy);
protected:
	template <size_t FuncTy>
	static UserFuncBase* factory() { return NULL; }
	static std::unordered_map<size_t, UserFuncBase* (*)()> factMap;
};
