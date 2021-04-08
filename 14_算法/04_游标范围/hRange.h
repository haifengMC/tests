#pragma once

enum VernierType
{
	VernierType_None,
	VernierType_Equal,
	VernierType_Unequal,
	VernierType_Greater,
	VernierType_Less,
	VernierType_GreaterEqual,
	VernierType_LessEqual,
};

//游标
class hVernier
{
	uint8_t _tp = VernierType_None;	//游标类型
	int _val = 0;		//游标值

public:
	hVernier(int val);
	operator int() const { return _val; }
};

class hRange
{
	std::set<hVernier> _vern;

	bool check(int val) const;
};
