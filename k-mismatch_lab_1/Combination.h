#pragma once
#include <vector>
#include <ostream>
#include "BinaryIntBaseSequence.h"

class Combination: public BinaryIntBaseSequence<Combination>
{
public:
	//constructor "inheritance"
	using BinaryIntBaseSequence::BinaryIntBaseSequence;

	static std::vector<Combination> generateAllCombinations(uint64_t length, uint64_t mismatchK);
};