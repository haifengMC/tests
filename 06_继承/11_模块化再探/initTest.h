#pragma once

struct CreateTest
{
	CreateTest() { std::cout << "CreateTest" << std::endl; }
	~CreateTest() { std::cout << "~CreateTest" << std::endl; }
};