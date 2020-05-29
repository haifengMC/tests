#pragma once
#include "vmacro.h"

#define RESET(X) \
		this->type = X; \
		v.v = NULL; \
		buf.clear(); 

#define OPERATOR_F(n, type_name, tp, va) \
		uValue& operator=(const tp& t)\
		{\
			RESET(type_name)\
			va = t;\
			return *this;\
		}\
		operator tp() { return (tp&)va; }

#define OPERATOR_CASE_F(n, type_name, tp, va) \
		case type_name:os << u.va;break

#define OPERATOR(...) \
		template<typename T>\
		uValue& operator=(const T& t)\
		{\
			RESET(uValueType_Void)\
			v.v = (void*)&t;\
			return *this;\
		}\
		operator void* () { return v.v; }\
		EXPAND(REPEAT_F_SEP(OPERATOR_F, 3, SEM_M, ##__VA_ARGS__))\
		friend std::ostream& operator<<(std::ostream& os, const uValue& u)\
		{\
			switch (u.getType())\
			{\
				EXPAND(REPEAT_N_F_SEP(7, OPERATOR_CASE_F, 3, SEM_M, ##__VA_ARGS__));\
				case uValueType_Void:os << u.v.v;break;\
				default:\
					os << "ERROR";\
					break;\
			}\
			return os;\
		}