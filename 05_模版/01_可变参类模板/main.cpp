#include <iostream>
#include <typeinfo>
using namespace std;

// 变长模板的声明
template<typename... A> class BMW {};  

template<typename Head, typename... Tail>  // 递归的偏特化定义
class BMW<Head, Tail...> : public BMW<Tail...>
{//当实例化对象时，则会引起基类的递归构造
public:
	BMW() : BMW<Tail...>(), head(Head())
	{
		printf("type: %s\n", typeid(Head).name());
	}
	BMW(const Head& h, Tail... t) : BMW<Tail...>(t...)
	{
		head = h;
	}
	
	Head head;

	bool operator==(const BMW<Head, Tail...>& bmw) const
	{
		if (head == bmw.head)
			return (BMW<Tail...>) * this == (BMW<Tail...>)bmw;
		else
			return false;
	}
	bool operator!=(const BMW<Head, Tail...>& bmw) const
	{
		return !(*this == bmw);
	}
	bool operator<(const BMW<Head, Tail...>& bmw) const
	{
		if (head < bmw.head) 
			return true;

		if (head == bmw.head) 
			return (BMW<Tail...>) * this < (BMW<Tail...>)bmw;

		return false;
	}
	bool operator>(const BMW<Head, Tail...>& bmw) const
	{
		return bmw < *this;
	}
	bool operator<=(const BMW<Head, Tail...>& bmw) const
	{
		return !(bmw < *this);
	}
	bool operator>=(const BMW<Head, Tail...>& bmw) const
	{
		return !(*this < bmw);
	}
	BMW<Head, Tail...>& operator()(const Head& h, Tail... t)
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

// 边界条件
template<> class BMW<>
{
protected:
	unsigned char tSize = 0;
public:
	bool operator==(const BMW<>& bmw) const { return true; }
	bool operator<(const BMW<>& bmw) const { return false; }
	BMW<>& operator()() { return *this; }
	void* operator[](const unsigned int& index) const { return NULL; }
}; 

template<typename Head, typename... Tail>
ostream& operator<<(ostream& os, const BMW<Head, Tail...>& bmw)
{
	os << bmw.head << " " << (BMW<Tail...>)bmw;
	return os;
}

ostream& operator<<(ostream& os, const BMW<>& bmw) { return os; }

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


	return 0;
}