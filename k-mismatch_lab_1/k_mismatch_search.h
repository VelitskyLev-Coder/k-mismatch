#pragma once

#include <string>
#include <map>
#include <vector>
#include <set>
#include "mcs.h"


class KMismatchSearch
{
public:
	KMismatchSearch();
	void initRandomText(size_t size, size_t alphabetSize, size_t seed = 0);
	const std::string& getText() const;
	std::map<std::string, std::vector<size_t>> naiveSearch(std::vector<std::string> queries, size_t maxMismatchs) const;
	std::map<std::string, std::set<size_t>> mcsSearch(std::vector<std::string> queries, size_t maxMismatchs, const MCS& mcs) const;
	
private:
	bool CheckQueryOnPosition(const std::string& query, int64_t position, size_t maxMismatchs) const;
	std::string text;

};

