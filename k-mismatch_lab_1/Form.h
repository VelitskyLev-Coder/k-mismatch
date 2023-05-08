#pragma once
#include "BinaryIntBaseSequence.h"
#include <vector>

class Form: public BinaryIntBaseSequence<Form>
{
public:
	//constructor "inheritance"
	using BinaryIntBaseSequence::BinaryIntBaseSequence;

	static std::vector<Form> generateAllForms(uint64_t length, uint64_t matches);
private:

};

