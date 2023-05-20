#pragma once
#include "binaryIntBaseSequence.h"
#include <vector>
#include "type_defs.h"
class Combination;

class Form: public BinaryIntBaseSequence<Form>
{
public:
	//constructor "inheritance"
	using BinaryIntBaseSequence::BinaryIntBaseSequence;

	static std::vector<Form> generateAllForms(uint64_t length, uint64_t matches);

	size_t getSize() const;
	std::string getStringFromPosition(const std::string& str, size_t pos) const;

	friend class Combination;



};

