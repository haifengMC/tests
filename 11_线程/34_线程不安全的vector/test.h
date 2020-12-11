using namespace std;
static mutex coutM;
#define COUT_LOCK(x) { lock_guard<mutex> lk(coutM); cout << "[" << setw(2) << setfill('0') << i << "]" << x << endl; }



void pSize1(const char* name, vector<int>& v, size_t n);
void pSize2(const char* name, vector<int>& v, size_t n);

class A
{
public:
	A() { cout << "A()" << endl; }
	A(const A&) { cout << "A(const A&)" << endl; }
	A(A&&) noexcept { cout << "A(A&&)" << endl; }
};

class B
{
public:
	B() { cout << "B()" << endl; }
	B(const B&) { cout << "B(const B&)" << endl; }
};

class C
{
public:
	C() { cout << "C()" << endl; }
	C(C&&) noexcept { cout << "C(C&&)" << endl; }
};

class D
{
	int id = 0;
	string name = "";

	friend ostream& operator<<(ostream& os, const D& d);
public:
	D(int id, const string& name) : id(id), name(name) {}

};
ostream& operator<<(ostream& os, const D& d);

struct AData1
{
	hRWLock lk;
	vector<int> v = { 1, 2, 3 };
	AData1& operator=(initializer_list<int> il);
};
ostream& operator<<(ostream& os, const AData1& data);

struct AItem1
{
	void pData(int i);
};

struct AMgr1
{
	static AData1* data;
	hVector<AItem1> items;
	void pData(size_t i);
};
void f1(AMgr1* a, int i);

struct AData2
{
	hVector<int> v = { 1, 2, 3 };
	AData2& operator=(initializer_list<int> il);
};
ostream& operator<<(ostream& os, const AData2& data);

struct AItem2
{
	AData2& data;

	AItem2(AData2& data) : data(data) {}

	void pData(int i);
};

struct AMgr2
{
	mutex m;
	AData2 data;
	hVector<AItem2> items;

	void pData(size_t i);
};
void f2(AMgr2* a, int i);
