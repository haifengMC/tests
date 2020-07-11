#pragma once

//������С������������
template<typename Key, typename Val>
class NumGen
{
	const Key minN;
	const Key maxN;
	Key endN;//βԪ��
	const std::map<Key, Val>& keyMap;//�󶨵�map
	std::set<Key> keySet;
public:
	NumGen(const std::map<Key, Val>& m, const Key& minN = 0, const Key& maxN = -1);
	size_t getNum(Key* pKey, size_t num);
	template<size_t N>
	size_t getNum(Key(&)[N]);
	void checkTimer();//����ʱ��
};
