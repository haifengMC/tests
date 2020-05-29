#pragma once
#include "uValueMacro.h"

enum uValueType
{
	uValueType_Void,
	uValueType_Int,
	uValueType_Uint,
	uValueType_Int64, 
	uValueType_Uint64,
	uValueType_Float,
	uValueType_Double,
	uValueType_String,
};

union _uValue
{
	int64_t i;
	uint64_t u;
	double d;
	void* v;
};

class uValue
{
	uValueType type;
	_uValue v;
	std::string buf;

public:
	uValue() { RESET(uValueType_Void); }
	~uValue() { RESET(uValueType_Void); }

	const uValueType& getType() const { return type; }

	OPERATOR//operator=() operator type() //operator<<(os, uVal)
	(
		uValueType_Int, int, v.i,
		uValueType_Uint, unsigned int, v.u,
		uValueType_Int64, long, v.i,
		uValueType_Uint64, unsigned long, v.u,
		uValueType_Float, float, v.d,
		uValueType_Double, double, v.d,
		uValueType_String, std::string, buf,
		uValueType_String, char* const, buf,
	)
};

