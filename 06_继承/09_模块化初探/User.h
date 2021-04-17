#pragma once


struct UserFuncBase;
struct User
{
	std::map<size_t, UserFuncBase*> funcMap;

	void loadFunc();
	void printEveryFunc();
};