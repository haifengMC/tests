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

//�α�
class hVernier
{
	uint8_t _tp = VernierType_None;	//�α�����
	int _val = 0;		//�α�ֵ

public:
	hVernier(int val);
	operator int() const { return _val; }
};

class hRange
{
	std::set<hVernier> _vern;

	bool check(int val) const;
};
