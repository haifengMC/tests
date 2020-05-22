#include <iostream>

using namespace std;

#define DEL(X) if (X) { delete X; X = 0; }


template<typename T>
class SingletonFactory
{
public:
	static T* instance() { return new T(); }
};

template<typename T, typename TFty = SingletonFactory<T>>
class Singleton
{
	static T* pInst;
	Singleton(const Singleton&) = delete;
	const Singleton& operator=(const Singleton&) = delete;
public:
	Singleton() {}
	~Singleton() { delMe(); }

	static T& getMe()
	{
		if (!pInst)
			pInst = TFty::instance();

		return *pInst;
	}

	static void delMe() { DEL(pInst) }
};
template<typename T, typename TFty>
T* Singleton<T, TFty>::pInst = NULL;

class cA : public Singleton<cA>
{
public:
	cA() {}

	int i1 = 10;
	int i2 = 20;
};

template<typename T>
class cBFty : SingletonFactory<T>
{
public:
	static T* instance() { return new T(cA::getMe().i2, cA::getMe().i1); }
};

class cB : public Singleton<cB, cBFty<cB>>
{
public:
	cB(int i1, int i2) { this->i1 = i1; this->i2 = i2; }

	int i1 = 0;
	int i2 = 0;
};

int main()
{
	cout << cA::getMe().i1 << " " << cA::getMe().i2 << endl;
	cout << cB::getMe().i1 << " " << cB::getMe().i2 << endl;

	return 0;
}
