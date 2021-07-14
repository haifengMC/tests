#include <iostream>

using namespace std;

/*
�����̳�
	1������public     �����б�Ϊ  public
	2������protected  �����б�Ϊ protected
	3������ private   �����з��ʲ���
�����̳�
	1������public     �����б�Ϊ protected
	2������protected  �����б�Ϊ protected
	3������private    �����з��ʲ���
˽�м̳�
	1������public     �����б�Ϊ private
	2������protected  �����б�Ϊ private
	3������private    �����з��ʲ���
*/

class Base 
{
public:	
	size_t i1 = 1;
protected:
	size_t i2 = 2;
private:
	size_t i3 = 3;
};

struct A : public Base
{
	void printI1() { cout << i1 << endl; }
	void printI2() { cout << i2 << endl; }
	void printI3() { /*Err privte cout << i3 << endl;*/ }
};

struct B : protected Base
{
	void printI1() { cout << i1 << endl; }
	void printI2() { cout << i2 << endl; }
	void printI3() { /*Err privte cout << i3 << endl;*/ }
};

struct C : private Base
{
	void printI1() { cout << i1 << endl; }
	void printI2() { cout << i2 << endl; }
	void printI3() { /*Err privte cout << i3 << endl;*/ }
};

int main()
{
	A a;
	cout << a.i1 << endl;
	//Err protected cout << a.i2 << endl;
	//Err privte	cout << a.i3 << endl;

	B b;
	//Err protected cout << b.i1 << endl;
	//Err protected cout << b.i2 << endl;
	//Err privte	cout << b.i3 << endl;

	C c;
	//Err privte	cout << c.i1 << endl;
	//Err privte	cout << c.i2 << endl;
	//Err privte	cout << c.i3 << endl;

	return 0;
}