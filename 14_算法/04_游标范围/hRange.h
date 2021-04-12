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

//�α�
class hVernier
{
	uint8_t _ty = VernierType_None;	//�α�����
	int _val = 0;		//�α�ֵ

public:
	hVernier(int val);
	hVernier(uint8_t ty, int val);

	uint8_t getTy() const { return _ty; }
	void setTy(uint8_t ty) { _ty = ty; }
	int getVal() const { return _val; }
	bool check(int val) const;
};

class hRange
{
	std::map<int, hVernier> _vern;
public:
	void insert(uint8_t tp, int val);
	bool check(int val) const;
};
