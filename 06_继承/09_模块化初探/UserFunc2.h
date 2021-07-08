#pragma once

class UserFuncBase;
struct UserFunc2 : public UserFuncBase
{
	void printMe();
	void initEvent();

	struct RegUserFunc2 { RegUserFunc2(); };
private:
	void doRegAct1();
	void doRegAct2();
	void doEvt1Act();
};