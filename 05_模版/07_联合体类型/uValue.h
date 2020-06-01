#pragma once
#include "vcommon.h"
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
	uValueType_String
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
	uValueType type = uValueType::uValueType_Void;
	_uValue v = _uValue();
	std::string buf;

public:
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

#undef RESET
#undef OPERATOR_F
#undef OPERATOR_CASE_F
#undef OPERATOR
