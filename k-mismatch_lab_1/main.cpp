#include "Combination.h"
#include "Form.h"
#include <iostream>
#include <vector>
#include <chrono>
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
	/*auto combinations = Combination::generateAllCombinations(35, 12);
	for (auto combination : combinations) {
		//cout << combination << endl;
		s++;
	}
	cout << s;*/
	auto forms = Form::generateAllForms(64, 3);
	for (auto form : forms) {
		cout << form << endl;
		s++;
	}
	cout << s;
	return 0;
}
