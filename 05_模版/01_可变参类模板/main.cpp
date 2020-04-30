#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;


// 变长模板的声明
template<typename... A> class BMW {};  

// 边界条件
template<> class BMW<>
{
protected:
	unsigned short tNum = 0;
public:
	const unsigned short& num() const { return tNum; }
	unsigned int size() const { return 0; }
	bool fill(void* buf, const unsigned int& len) { return true; }

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

	Head head;

	unsigned int size() const { return sizeof(head) + this->BMW<Tail...>::size(); }
	bool fill(void* buf, const unsigned int& len)
	{
		if (!buf || len < size())
			return false;

		memcpy(buf, &head, sizeof(head));

		return this->BMW<Tail...>::fill((char*)buf + sizeof(head), len - sizeof(head));
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

template<typename Head, typename ...Tail>
unsigned int BMW<Head, Tail...>::size() const { return head.size() + this->BMW<Tail...>::size(); }
/*
template<typename... Tail>
class BMW<std::string, Tail...>
{
public:
	BMW() : BMW<Tail...>(), head("")
	{
		BMW<>::tNum = sizeof...(Tail) + 1;
	}
	BMW(const string& h, Tail... t) : BMW<Tail...>(t...)
	{
		head = h;
		BMW<>::tNum = sizeof...(Tail) + 1;
	}

	unsigned int size() const { return head.size() + this->BMW<Tail...>::size(); }
	bool fill(void* buf, const unsigned int& len)
	{
		if (!buf || len < size())
			return false;

		memcpy(buf, head.c_str(), head.size());

		return this->BMW<Tail...>::fill((char*)buf + head.size(), len - head.size());
	}
	std::string head;
};
*/

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

	char buf[4] = "";
	BMW<char, char, char> car4('a', 'b', 'c');
	car4.fill(buf, sizeof(buf));
	cout << buf << endl;

	/*
	BMW<char, char, string> car5('a', 'b', "hello world");
	cout << car5.size() << endl;
	*/

	return 0;
}