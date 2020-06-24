#include <vector>
#include <thread>
#include <mutex>

#include "Philosopher.h"

int main()
{
	PhilosopherMgr m(200);

	m.run();
	m.join();

	return 0;
}