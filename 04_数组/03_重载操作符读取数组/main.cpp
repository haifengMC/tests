#include <iostream>

using namespace std;

template<size_t size>
ostream& operator<<(ostream& os, const int(&arr)[size])
{
	for (const int& i : arr)
		os << i << " ";
	return os;
}

class CArr
{
	int arr[3];
	typedef int(&ArrRef)[3];
	typedef const int(&ConstArrRef)[3];
public:
	CArr() { memset(arr, 0, sizeof(arr)); }
	
	operator ArrRef() { return arr; }
	operator ConstArrRef() const { return arr; }


	template<size_t size>
	CArr& operator=(const int(&arrT)[size])
	{
		memset(arr, 0, sizeof(arr));
		size_t count = 0;
		for (int& i : arr)
		{
			if (count >= size)
				break;
			i = arrT[count++];
		}
		return *this;
	}

	friend ostream& operator<<(ostream& os, const CArr& arr)
	{
		const int(&arrT)[3] = arr;
		for (const int& i : arrT)
			os << i << " ";
		return os;
	}
};

class CArr2
{
	int arr[2][3];
	typedef int(&ArrRef)[2][3];
public:
	CArr2() { memset(arr, 0, sizeof(arr)); }

	operator ArrRef() { return arr; }
	//operator ConstArrRef() const { return arr; }

	template<size_t size1, size_t size2>
	CArr2& operator=(const int(&arrT)[size1][size2])
	{
		memset(arr, 0, sizeof(arr));
		size_t cnt1 = 0, cnt2 = 0;
		for (int(&ar)[3] : arr)
		{
			if (cnt1 >= size1)
				break;
			for (int& i : ar)
			{
				if (cnt2 >= size2)
					break;
				i = arrT[cnt1][cnt2++];
			}
			++cnt1;
			cnt2 = 0;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& os, const CArr2& arr)
	{
		bool first1 = true;
		const int(&arrT)[2][3] = arr.arr;
		for (const int(&ar)[3] : arrT)
		{
			if (first1) first1 = false;
			else os << ", ";
			bool first2 = true;
			for (const int& i : ar)
			{
				if (first2) first2 = false;
				else os << " ";

				os << i;
			}
		}
		return os;
	}
};


int main()
{
	int arr1[3] = { 1, 2, 3 };
	cout << arr1 << endl;
	int arr2[4] = { 4, 5, 6, 7 };
	cout << arr2 << endl;

	CArr ca;
	cout << ca << endl;
	ca = { 1, 2, 3 };
	cout << ca << endl;
	ca = { 4 };
	cout << ca << endl;
	ca = { 5, 6, 7, 8 };
	cout << ca << endl;
	ca = {};
	cout << ca << endl;

	CArr2 ca2;
	cout << ca2 << endl;
	ca2 = { {1, 2, 3}, {4, 5, 6} };
	cout << ca2 << endl;
	ca2 = { {1, 2}, {3, 4} };
	cout << ca2 << endl;
	ca2 = { {1, 2, 3, 4}, {5, 6, 7, 8} };
	cout << ca2 << endl;
	cout << ca2[1][2] << endl;
	ca2 = {};
	cout << ca2 << endl;

	return 0;
}
