#pragma once

class User
{
	friend class UserFuncBase;
	std::unordered_map<size_t, UserFuncBase*> funcMap;
	using Act = std::function<void()>;
	using ActList = std::list<Act>;
	using ActGrp = std::map<uint8_t, ActList>;
	std::map<size_t, ActGrp> evtMap;
	std::list<std::pair<size_t, uint8_t>> curEvtList;
public:
	void loadFunc();
	void printEveryFunc();
	void initEvents();
	bool doEvents();
};