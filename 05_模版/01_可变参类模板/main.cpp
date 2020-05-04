#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

template<typename T> 
class Copier//拷贝适配器
{
	T* pt; 
	const T* cpt;
public:
	size_t size() const
	{
		if (cpt) return  sizeof(*cpt);
		else return 0;
	}

	unsigned int read(void* buf, const unsigned int& len)
	{
		if (!pt || !buf || len < size())
			return false;

		memcpy(pt, buf, sizeof(*pt));
		return size();
	}

	unsigned int write(void* buf, const unsigned int& len) const
	{
		if (!cpt || !buf || len < size())
			return false;

		memcpy(buf, cpt, sizeof(*cpt));
		return size();
	}

	Copier(T& t) : pt(&t), cpt(&t) {}
	Copier(const T& t) : pt(NULL), cpt(&t) {}
};

template<> class Copier<std::string>//拷贝适配器
{
	std::string* pt;
	const std::string* cpt;
public:
	size_t size() const
	{
		if (cpt) return cpt->size();
		else return 0;
	}

	unsigned int  read(void* buf, const unsigned int& len) { return 0; }

	unsigned int  write(void* buf, const unsigned int& len) const
	{
		if (!cpt || !buf || len < size())
			return false;

		memcpy(buf, cpt->c_str(), cpt->size());
		return size();
	}

	Copier(std::string& t) : pt(&t), cpt(&t) {}
	Copier(const std::string& t) : pt(NULL), cpt(&t) {}
};

// 变长模板的声明
template<typename... A> class BMW {};  

// 边界条件
template<> class BMW<>
{
protected:
	unsigned short tNum = 0;
public:
	const unsigned short& num() const { return tNum; }
	size_t size() const { return 0; }
	unsigned int read(void* buf, const unsigned int& len) { return 0; }
	unsigned int write(void* buf, const unsigned int& len) const { return 0; }

	bool operator==(const BMW<>& bmw) const { return true; }
	bool operator<(const BMW<>& bmw) const { return false; }
	BMW<>& operator()() { return *this; }
	void* operator[](const unsigned int& index) const { return NULL; }
};

template<typename Head, typename... Tail>  // 递归的偏特化定义
class BMW<Head, Tail...> : public BMW<Tail...>
{//当实例化对象时，则会引起基类的递归构造
public:
	BMW() : BMW<Tail...>(), head(Head())
	{
		printf("type: %s\n", typeid(Head).name());
		BMW<>::tNum = sizeof...(Tail) + 1;
	}
	BMW(const Head& h, const Tail&... t) : BMW<Tail...>(t...)
	{
		head = h;
		BMW<>::tNum = sizeof...(Tail) + 1;
	}
	BMW(Head&& h, Tail&&... t) : BMW<Tail...>(t...)
	{
		head = std::move(h);
		BMW<>::tNum = sizeof...(Tail) + 1;
	}

	Head head;

	size_t size() const { return Copier<Head>(head).size() + this->BMW<Tail...>::size(); }
	unsigned int read(void* buf, const unsigned int& len)
	{
		if (!buf || len < size())
			return 0;
		Copier<Head> cHead(head);
		
		unsigned int n = cHead.read(buf, len);
		if (n)
			return n + this->BMW<Tail...>::read((char*)buf + cHead.size(), len - cHead.size());
		else
			return n;
	}

	unsigned int write(void* buf, const unsigned int& len) const
	{
		if (!buf || len < size())
			return 0;
		Copier<Head> cHead(head);

		unsigned int n = cHead.write(buf, len);
		if (n)
			return n + this->BMW<Tail...>::write((char*)buf + cHead.size(), len - cHead.size());
		else
			return n;
	}

	//==, !=
	bool operator==(const BMW<Head, Tail...>& bmw) const
	{
		if (head == bmw.head)
			return (BMW<Tail...>) * this == (BMW<Tail...>)bmw;
		else
			return false;
	}
	bool operator!=(const BMW<Head, Tail...>& bmw) const { return !(*this == bmw); }

	//<, >, <=, >=
	bool operator<(const BMW<Head, Tail...>& bmw) const
	{
		if (head < bmw.head) 
			return true;

		if (head == bmw.head) 
			return (BMW<Tail...>) * this < (BMW<Tail...>)bmw;

		return false;
	}
	bool operator>(const BMW<Head, Tail...>& bmw) const { return bmw < *this; }
	bool operator<=(const BMW<Head, Tail...>& bmw) const { return !(bmw < *this); }
	bool operator>=(const BMW<Head, Tail...>& bmw) const { return !(*this < bmw); }

	BMW<Head, Tail...>& operator()(const Head& h, const Tail&... t)
	{
		head = h;
		this->BMW<Tail...>::operator()(t...);
		return *this;
	}
	//Head& operator[](const unsigned int& index)
	void* operator[](const unsigned int& index)
	{
		if (!index) return &head;
		else return this->BMW<Tail...>::operator[](index - 1);
	}
};

template<typename Head, typename... Tail>
ostream& operator<<(ostream& os, const BMW<Head, Tail...>& bmw)
{
	if (sizeof...(Tail) + 1 == bmw.num()) os << "{";
	else os << ",";

	return os << bmw.head << (BMW<Tail...>)bmw;
}
ostream& operator<<(ostream& os, const BMW<>& bmw) { return os << "}"; }

int main()
{
	BMW<int, char, float> car1;
	cout << typeid(decltype(car1.head)).name() << endl;
	cout << typeid(decltype(car1.BMW<char, float>::head)).name() << endl;

	BMW<int, char, float> car2(1, 'a', 2.2f);
	cout << car2 << endl;
	BMW<int, char, float> car3(1, 'a', 2.2f);

	cout << (car1 == car2) << " " << (car2 == car3) << endl;
	cout << (car1 != car2) << " " << (car2 != car3) << endl;
	cout << (car1 < car2) << " " << (car2 < car3) << endl;
	cout << (car1 > car2) << " " << (car2 > car3) << endl;
	cout << (car1 <= car2) << " " << (car2 <= car3) << endl;
	cout << (car1 >= car2) << " " << (car2 >= car3) << endl;

	cout << car1 << endl;
	car1(2, 'b', 3.3f);
	cout << car1 << endl;

	cout << car1[0] << " " << *(int*)car1[0] << endl;
	cout << car1[1] << " " << *(char*)car1[1] << endl;
	cout << car1[2] << " " << *(float*)car1[2] << endl;
	cout << car1[3] << endl;

	cout << car1.num() << endl;
	cout << car1.BMW<char, float>::num() << endl;
	cout << car1.BMW<float>::num() << endl;
	cout << car1.BMW<>::num() << endl;

	car1 = { 3, 'c', 4.4f };
	cout << car1 << endl;
	cout << car1.size() << endl;
	cout << car1.BMW<char, float>::size() << endl;
	cout << car1.BMW<float>::size() << endl;
	cout << car1.BMW<>::size() << endl;

	char buf1[4] = "";
	BMW<char, char, char> car4('a', 'b', 'c');
	
	car4.write(buf1, sizeof(buf1));
	cout << buf1 << endl;
	
	BMW<char, char, string> car5('a', 'b', "hello world"), car8;
	cout << car5.size() << endl;

	char buf2[32] = "";
	cout << car5.write(buf2, sizeof(buf2)) << endl;
	cout << buf2 << endl;

	BMW<int, int, int> car6(1, 2, 3), car7;
	cout << car6 << car7 << endl;
	char buf3[32] = "";
	cout << car6.write(buf3, sizeof(buf3)) << endl;
	cout << buf3 << endl;
	cout << car7.read(buf3, sizeof(buf3)) << endl;
	cout << car7 << endl;

	cout << car8.read(buf2, sizeof(buf2)) << endl;
	cout << car8 << endl;

	BMW<char, string, char> car9('a', "hello world", 'b'), car10;
	cout << car9 << car10 << endl;
	char buf4[32] = "";
	cout << car9.write(buf4, sizeof(buf4)) << endl;
	cout << car9 << endl;
	cout << car10.read(buf4, sizeof(buf4)) << endl;
	cout << car10 << endl;


	return 0;
}