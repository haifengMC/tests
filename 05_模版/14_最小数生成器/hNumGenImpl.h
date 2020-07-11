#pragma once

template<typename Key, typename Val>
NumGen<Key, Val>::NumGen(const std::map<Key, Val>& m,
	const Key& minN, const Key& maxN) : keyMap(m),
	minN(minN < maxN ? minN : maxN), maxN(minN < maxN ? maxN : minN) 
{
	endN = minN;
}

template<typename Key, typename Val>
size_t NumGen<Key, Val>::getNum(Key* pKey, size_t num)
{
	if (maxN <= minN + keyMap.size())
	{
		std::cout << "�Ѵ�������ɷ�Χ" << std::endl;
		return 0;//�Ѵ�������ɷ�Χ
	}
 
	if (num + endN > maxN  + keySet.size() &&//����>��������
		endN > minN + keyMap.size() + keySet.size())//�����и��¿ռ�
	{
		std::cout << "����������" << std::endl;
		checkTimer();
	}
	size_t n = 0;

	for (typename std::set<Key>::const_iterator it = keySet.begin(); 
		it != keySet.end() && n < num; it = keySet.erase(it), ++n)
		pKey[n] = *it;

	if (n >= num)
		return n;

	for (; n < num && endN < maxN; ++n, ++endN)
		pKey[n] = endN;

	return n;
}

template<typename Key, typename Val>
template<size_t N>
size_t NumGen<Key, Val>::getNum(Key (&key)[N])
{
	return getNum(key, N);
}

template<typename Key, typename Val>
void NumGen<Key, Val>::checkTimer()
{
	Key checkKey = minN;
	for (const std::pair<Key, Val>& p : keyMap)
	{
		for (; checkKey < p.first; ++checkKey)
			keySet.insert(checkKey);

		if (checkKey == p.first)
			++checkKey;
	}
	endN = keyMap.rbegin()->first + 1;
}

