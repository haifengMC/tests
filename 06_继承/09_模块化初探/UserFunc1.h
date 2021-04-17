#pragma once

struct UserFuncBase;
struct UserFunc1 : public UserFuncBase
{
	void printMe();

	struct RegUserFunc1 { RegUserFunc1(); };
};