#pragma once

namespace ASpace
{
	struct A
	{
		std::string name = "A";
		const char* getName() const;
	};

	namespace BSpace
	{
		struct B
		{
			std::string name = "B";
			const char* getName() const;
		};

	}

	namespace CSpace
	{
		struct C
		{
			std::string name = "C";
			const char* getName() const;
		};

	}


}