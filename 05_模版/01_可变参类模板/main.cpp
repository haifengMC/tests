#include <iostream>
#include <typeinfo>
using namespace std;

template<typename... A> class BMW {};  // �䳤ģ�������

template<typename Head, typename... Tail>  // �ݹ��ƫ�ػ�����
class BMW<Head, Tail...> : public BMW<Tail...>
{//��ʵ��������ʱ������������ĵݹ鹹��
public:
	BMW() : BMW<Tail...>(), head(Head())
	{
		printf("type: %s\n", typeid(Head).name());
	}
	BMW(Head h, Tail... tail) : BMW<Tail...>(tail...)
	{
		head = h;
	}

	Head head;

	bool operator==(const BMW<Head, Tail...>& bmw) const
	{
		if (head == bmw.head)
		{
			return (BMW<Tail...>)*this == (BMW<Tail...>)bmw;
		}
		return false;
	}
};

// �߽�����
template<> class BMW<>
{
public:
	bool operator==(const BMW<>& bmw) const { return true; }
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

	BMW<int, char, float> car2(1, 'a', 2.0f);
	cout << car2 << endl;
	BMW<int, char, float> car3(1, 'a', 2.0f);

	cout << (car1 == car2) << (car2 == car3) << endl;

	return 0;
}