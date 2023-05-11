#include "combination.h"
#include "form.h"
#include <iostream>
#include <vector>
#include <chrono>
#include "mcs.h"

class SimpleTimer
{
public:
	SimpleTimer()
	{
		start = std::chrono::high_resolution_clock::now();
	}
	~SimpleTimer()
	{
		end = std::chrono::high_resolution_clock::now();
		std::cout << "\n\nElapsed time:\t " << ((std::chrono::duration<double>)(end - start)).count() << " seconds\n";
	}


private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
};

using namespace std;

int main() {
	SimpleTimer timer;
	int64_t s = 0;
	int length = 25;
	auto mcs = MCS::buildMCSNaiveMultithreaded(length, length * 40 / 100, 5);

	std::cout << "\nMCS:\n";
	for (auto form : mcs.getMcsForms()) {
		cout << form << '\n';
		s++;
	}
	cout << "\nWith total length of " << s << " forms\n";
	std::cout << "____________________\n";
	return 0;
}
