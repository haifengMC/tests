#pragma once

struct UserFuncBase;
struct UserFunc2 : public UserFuncBase
{
	void printMe();

	struct RegUserFunc2 { RegUserFunc2(); };
};