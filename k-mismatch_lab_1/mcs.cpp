#include "mcs.h"
#include <algorithm>
#include <map>
#include <execution>

//TODO remove
#include <iostream>

const std::vector<Form>& MCS::getMcsForms() const
{
	return this->mcsForms;
}

MCS MCS::buildMCSNaiveMultithreaded(uint64_t length, uint64_t mismatchK, uint64_t matchesPerForm)
{
	MCS resultMCS;
	std::cout << "Start to build MCS for lenth: " << length << ", mismaychK: " << mismatchK << ", matchesPerForm: " << matchesPerForm << '\n';
	auto combinations = Combination::generateAllCombinations(length, mismatchK);
	auto forms = Form::generateAllForms(length, matchesPerForm);
	std::cout << "Number of all combinations: " << combinations.size() << "\n";
	std::cout << "Number of all forms: " << forms.size() << "\n";
	while (!combinations.empty())
	{
		std::cout << "Remaining combinations: " << combinations.size() << std::endl;

		//Calcualate the form that contributes for the maximal number of combinations
		auto bestFormToCombinationNumberPair = std::transform_reduce(
			std::execution::par,  // Use a parallel execution policy
			forms.begin(), forms.end(),  // Input range
			std::pair<Form, uint64_t>{forms.front(), 0},  // Initial value

			// Binary operation for reduction
			// It takes two pairs of <Form, uint64_t> as input and returns the one with the greater count.
			[](const std::pair<Form, uint64_t>& a, const std::pair<Form, uint64_t>& b) {
				if (a.second == b.second)
					return a.first < b.first ? a : b;
				return a.second > b.second ? a : b;
			},

			// Unary operation for transformation
			// It takes a Form as input and calculates the number of combinations containing that form.
			// Returns a pair of <Form, uint64_t>, where the uint64_t value represents the count of combinations containing the form.
			[&combinations](const Form& form) {
				uint64_t curFormCombinationNumber = 0;
				// Iterate over each combination
				for (const Combination& combination : combinations) {
					if (combination.contains(form)) {
						curFormCombinationNumber++;
					}
				}
				// Return a pair containing the form and the count of combinations containing it
				return std::pair<Form, uint64_t>{form, curFormCombinationNumber};
			});


		//Adding the best form the the MCS
		resultMCS.mcsForms.push_back(bestFormToCombinationNumberPair.first);

		//Removing the combinations, containing the best form form
		auto newEndIt = std::remove_if(combinations.begin(), combinations.end(),
			[&bestFormToCombinationNumberPair](const Combination& combination) {
				return combination.contains(bestFormToCombinationNumberPair.first);
			});
		combinations.erase(newEndIt, combinations.end());

	}

	//std::sort(resultMCS.mcsForms.begin(), resultMCS.mcsForms.end());
	
	return resultMCS;
}


std::tuple<std::vector<Combination>, std::vector<Form>> 
MCS::buildFullCombinationsAndForms(uint64_t length, uint64_t mismatchK, uint64_t matchesPerForm)
{
	return std::make_tuple(
		Combination::generateAllCombinations(length, mismatchK),
		Form::generateAllForms(length, matchesPerForm));
}


MCS::MCS()
{
	this->mcsForms = std::vector<Form>();
}
