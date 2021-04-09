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
	VernierType_Max
};

//游标
class hVernier
{
	uint8_t _ty = VernierType_None;	//游标类型
	int _val = 0;		//游标值

public:
	hVernier(int val);
	hVernier(uint8_t ty, int val);
	operator int() const { return _val; }

	bool check(int val) const;
};

class hRange
{
	std::set<hVernier> _vern;
public:
	void inserVern(uint8_t tp, int val);

	bool check(int val) const;
};
