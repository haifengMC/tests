#include <string>
#include "test.h"

namespace ASpace
{
	const char* A::getName() const
	{
		return name.c_str();
	}
	namespace BSpace
	{
		const char* B::getName() const
		{
			return name.c_str();
		}
	}
	namespace CSpace
	{
		const char* C::getName() const
		{
			return name.c_str();
		}
	}

}
