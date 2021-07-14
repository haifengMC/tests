#include <iostream>

using namespace std;

/*
公共继承
	1父类中public     子类中变为  public
	2父类中protected  子类中变为 protected
	3父类中 private   子类中访问不到
保护继承
	1父类中public     子类中变为 protected
	2父类中protected  子类中变为 protected
	3父类中private    子类中访问不到
私有继承
	1父类中public     子类中变为 private
	2父类中protected  子类中变为 private
	3父类中private    子类中访问不到
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