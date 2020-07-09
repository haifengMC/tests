#pragma once

class B
{
public:
	int i;
	B(int i) : i(i) {}
	void printB()
	{
		std::cout << "B:" << i << std::endl;
	}
};