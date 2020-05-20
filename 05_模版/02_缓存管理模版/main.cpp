#include <iostream>
#include <list>
#include <map>

using namespace std;

template<typename T = unsigned short, typename TC = unsigned char, typename C = unsigned char>
class BufferCountData
{
	C index = 0;
	T offset = 0;
	std::string bufName;
	T size = 0;
	TC count = 0;
	T total = 0;
public:
	BufferCountData(const std::string& name, const T& size, const T& count) : index(0), bufName(name), count(count), size(size), total(count* size) {}
	const std::string& getName() const { return bufName; }
	bool isVaild() const { return total ? true : false; }
	void setIndex(const T& index) { this->index = index; }
	void setOffset(const T& offset) { this->offset = offset; }
	const C& getIndex() const { return index; }
	const T& getSize() const { return size; }
	const TC& getCount() const { return count; }
	const T& getTotal() const { return total; }
	T getOffset(const TC& cntId) const
	{
		if (isVaild() && cntId < count)
			return cntId * size;

		return 0;
	}
	T operator[](const TC& cntId) const { return getOffset(cntId); }
};

template<typename T = unsigned short, typename TC = unsigned char, typename C = unsigned char>
class BufferCountManager
{
	C index = 0;
	T size = 0;
	std::list<BufferCountData<T, TC, C>> bufCntData;
	std::map<C, BufferCountData<T, TC, C>*> indexMap;
	std::map<std::string, BufferCountData<T, TC, C>*> nameMap;
public:
	const T& getSize() const { return size; }

	bool addData(const std::string& name, const T& size, const T& count)
	{
		BufferCountData<T, TC, C> bc(name, size, count);
		if (!bc.isVaild())
			return false;

		if (nameMap.find(bc.getName()) != nameMap.end())
			return false;

		bc.setIndex(index++);
		bc.setOffset(this->size);
		this->size += bc.getTotal();

		typename std::list<BufferCountData<T, TC, C>>::iterator it = bufCntData.insert(bufCntData.end(), std::move(bc));
		indexMap.insert(std::make_pair(it->getIndex(), &*it));
		nameMap.insert(std::make_pair(it->getName(), &*it));

		return true;
	}
	typename std::map<C, BufferCountData<T, TC, C>*>::const_iterator begin() const { return indexMap.begin(); }
	typename std::map<C, BufferCountData<T, TC, C>*>::const_iterator end() const { return indexMap.end(); }

	const BufferCountData<T, TC, C>* getDataByName(const std::string& name) const
	{
		typename std::map<std::string, BufferCountData<T, TC, C>*>::const_iterator it = nameMap.find(name);
		if (it == nameMap.end())
			return NULL;

		return it->second;
	}

	const BufferCountData<T, TC, C>* getDataById(const C& index) const
	{
		typename std::map<C, BufferCountData<T, TC, C>*>::const_iterator it = indexMap.find(index);
		if (it == indexMap.end())
			return NULL;

		return it->second;
	}

	const BufferCountData<T, TC, C>* operator[](const std::string& name) const
	{
		typename std::map<std::string, BufferCountData<T, TC, C>*>::const_iterator it = nameMap.find(name);
		if (it == nameMap.end())
			return NULL;

		return it->second;
	}

	const BufferCountData<T, TC, C>* operator[](const C& index) const
	{
		typename std::map<C, BufferCountData<T, TC, C>*>::const_iterator it = indexMap.find(index);
		if (it == indexMap.end())
			return NULL;

		return it->second;
	}
};

template<typename T, typename TC, typename C>
std::ostream& operator<<(std::ostream& os, const BufferCountManager<T, TC, C>& bufCntMgr)
{
	for (std::pair<C, BufferCountData<T, TC, C>*> it: bufCntMgr)
	{
		os << it.second->getName() << " ";
	}

	return os;
}

int main()
{
	BufferCountManager<> mgr;
	mgr.addData("vertex", sizeof(float), 2 * 3);
	mgr.addData("color", sizeof(float), 3 * 3);

	cout << mgr.getSize() << " " << mgr[0]->getTotal() << " " << mgr[1]->getTotal() << endl;
	cout << mgr << endl;
	
	return 0;
}