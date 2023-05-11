#pragma once
#include <vector>
#include <ostream>
#include "form.h"
#include "set"
#include "type_defs.h"
class Combination: public BinaryIntBaseSequence<Combination>
{
public:
	//constructor "inheritance"
	using BinaryIntBaseSequence::BinaryIntBaseSequence;
	bool contains(const Form& form) const;
	std::set<Form> getAllForms(uint64_t matches) const;
	static std::vector<Combination> generateAllCombinations(uint64_t length, uint64_t mismatchK);
};