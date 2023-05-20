#include "combination.h"
#include "form.h"
#include <iostream>
#include <vector>
#include <chrono>
#include "mcs.h"
#include "k_mismatch_search.h"
#include <numeric>
#include <fstream>

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

std::vector<std::string> getSubstrings(const std::string& input, int N, int length) {
	std::vector<std::string> substrings;
	for (int i = 0; i < N; i++) {
		substrings.push_back(input.substr(i * length, length));
	}
	return substrings;
}

int main() {
	//timing section
	{
		SimpleTimer timer;
		KMismatchSearch kMismatchSearch;

		int length = 23;
		int misMatchs = length * 40 / 100;
		int alphabetSize = 10;
		int numberOfQueries = 10000;
		size_t sizeOfText = 100000000; // 100M 
		int matchesPerForm = 5;

		kMismatchSearch.initRandomText(sizeOfText, alphabetSize, 0);
		std::vector<std::string> queries;
		for (int i = 0; i < numberOfQueries; i++) {
			queries.push_back(kMismatchSearch.getText().substr(i * length, length));
		}
		/*auto result = kMismatchSearch.naiveSearch(queries, misMatchs);
		std::ofstream outFile("naive_test_results.txt");

		outFile << kMismatchSearch.getText() << std::endl;
		for (auto& [query, positions] : result)
		{
			outFile << std::endl;
			outFile << query << " ";
			for (auto position : positions)
				outFile << position << " ";
		}

		outFile.close();
		*/
		auto mcs = MCS::buildMCSNaiveMultithreaded(length, misMatchs, matchesPerForm);
		auto result = kMismatchSearch.mcsSearch(queries, misMatchs, mcs);
		//auto result = kMismatchSearch.naiveSearch(queries, misMatchs);
		std::ofstream outFile("mcs_search_results_5.txt");

		outFile << kMismatchSearch.getText() << std::endl;
		for (auto& [query, positions] : result)
		{
			outFile << std::endl;
			outFile << query << " ";
			for (auto position : positions)
				outFile << position << " ";
		}

		outFile.close();
		
		/*int64_t s = 0;
		int length = 22;
		auto mcs = MCS::buildMCSNaiveMultithreaded(length, length * 40 / 100, 7);
		*/
		int64_t s = 0;
		std::cout << "\nMCS:\n";
		for (auto& form : mcs.getMcsForms()) {
			cout << form << '\n';
			s++;
		}
		cout << "\nWith total length of " << s << " forms\n";
		std::cout << "____________________\n";
		

	}

	std::cin.ignore();
	return 0;
}
