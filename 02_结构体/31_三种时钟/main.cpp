// copied from http://www.informit.com/articles/article.aspx?p=1881386&seqNum=2;
// Author: Nicolai M. Josuttis

#include <thread>
#include <chrono>
#include <iostream>
#include <iomanip>

template <typename C>
void printClockData()
{
	using namespace std;

	cout << "- precision: ";
	// if time unit is less or equal one millisecond
	typedef typename C::period P;// type of time unit
	if (ratio_less_equal<P, milli>::value) {
		// convert to and print as milliseconds
		typedef typename ratio_multiply<P, kilo>::type TT;
		cout << fixed << double(TT::num) / TT::den
			<< " milliseconds" << endl;
	}
	else {
		// print as seconds
		cout << fixed << double(P::num) / P::den << " seconds" << endl;
	}
	cout << "- is_steady: " << boolalpha << C::is_steady << endl;
}

uint64_t getNow()
{
	const auto& now = std::chrono::steady_clock::now();
	typedef typename std::ratio_multiply<now::period, std::kilo> KiloPeriod;
	return now::period / KiloPeriod::den;
}

int main()
{
	std::cout << "system_clock: " << std::endl;
	printClockData<std::chrono::system_clock>();
	std::cout << "\nhigh_resolution_clock: " << std::endl;
	printClockData<std::chrono::high_resolution_clock>();
	std::cout << "\nsteady_clock: " << std::endl;
	printClockData<std::chrono::steady_clock>();

	std::cout << getNow() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << getNow() << std::endl;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}