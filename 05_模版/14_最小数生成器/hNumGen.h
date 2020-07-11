#pragma once

//生成最小可用数生成器
template<typename Key, typename Val>
class NumGen
{
	const Key minN;
	const Key maxN;
	Key endN;//尾元素
	const std::map<Key, Val>& keyMap;//绑定的map
	std::set<Key> keySet;
public:
	NumGen(const std::map<Key, Val>& m, const Key& minN = 0, const Key& maxN = -1);
	size_t getNum(Key* pKey, size_t num);
	template<size_t N>
	size_t getNum(Key(&)[N]);
	void checkTimer();//检测计时器
};
