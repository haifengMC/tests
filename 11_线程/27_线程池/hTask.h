#pragma once


namespace hThread
{
	class Task
	{
		size_t id;
		size_t weight;//Ȩ��
	public:
		const size_t& getId() const { return id; }
		const size_t& getWeight() const { return weight; }
	};
}