#pragma once
#include <vector>
#include "combination.h"
#include "form.h"
#include <tuple>
class MCS
{
public:
	const std::vector<Form>& getMcsForms() const;
	static MCS buildMCSNaive(uint64_t length, uint64_t mismatchK, uint64_t matchesPerFormint);
	static MCS buildMCSForm2CombMap(uint64_t length, uint64_t mismatchK, uint64_t matchesPerFormint);
	static std::tuple<std::vector<Combination>, std::vector<Form>>
		buildFullCombinationsAndForms(uint64_t length, uint64_t kMismatch, uint64_t matchesPerForm);

private:
	std::vector<Form> mcsForms;
	// disaible constractor to outter usage
	MCS();
};

