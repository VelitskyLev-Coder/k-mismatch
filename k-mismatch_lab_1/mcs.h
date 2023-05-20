#pragma once
#include <vector>
#include "combination.h"
#include "form.h"
#include <tuple>
#include "type_defs.h"
class MCS
{
public:
	const std::vector<Form>& getMcsForms() const;
	static MCS buildMCSNaiveMultithreaded(uint64_t length, uint64_t mismatchK, uint64_t matchesPerForm);
	static std::tuple<std::vector<Combination>, std::vector<Form>>
		buildFullCombinationsAndForms(uint64_t length, uint64_t kMismatch, uint64_t matchesPerForm);

private:
	std::vector<Form> mcsForms;
	// disaible constractor to outter usage
	MCS();
};

