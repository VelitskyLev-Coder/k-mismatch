#include "mcs.h"
#include <algorithm>
#include <map>
//TODO remove
#include <iostream>

const std::vector<Form>& MCS::getMcsForms() const
{
	return this->mcsForms;
}

MCS MCS::buildMCSNaive(uint64_t length, uint64_t mismatchK, uint64_t matchesPerForm)
{
	MCS resultMCS;
	auto [combinations, forms] = buildFullCombinationsAndForms(length, mismatchK, matchesPerForm);
	while (!combinations.empty())
	{
		std::cout << combinations.size() << std::endl;
		//Calcualate the form that contributes for the maximal number of combinations
		uint64_t maxCombinationNumber = 0;
		Form& bestForm = forms.front();
		for (const Form& form : forms)
		{
			uint64_t curFormCombinationNumber = 0;
			for (const Combination& combination : combinations)
				if (combination.contains(form))
					curFormCombinationNumber++;
			if (curFormCombinationNumber > maxCombinationNumber)
			{
				maxCombinationNumber = curFormCombinationNumber;
				bestForm = form;
			}
		}

		//Adding the best form the the MCS
		resultMCS.mcsForms.push_back(bestForm);

		//Removing the combinations, containing the best form form
		auto newEndIt = std::remove_if(combinations.begin(), combinations.end(),
			[&bestForm](const Combination& combination) {
				return combination.contains(bestForm);
			});
		combinations.erase(newEndIt, combinations.end());

	}
	
	return resultMCS;
}

MCS MCS::buildMCSForm2CombMap(uint64_t length, uint64_t mismatchK, uint64_t matchesPerForm)
{
	MCS resultMCS;
	std::cout << "Start to build MCS for lenth: " << length << ", mismaychK: " << mismatchK << ", matchesPerForm: " << matchesPerForm << '\n';
	auto [combinations, forms] = buildFullCombinationsAndForms(length, mismatchK, matchesPerForm);
	std::map<Combination, std::set<Form>> com2FormSetMap;
	for (const Combination& combination : combinations) {
		com2FormSetMap[combination] = combination.getAllForms(matchesPerForm);
	}
	std::cout << "Number of all combinations: " << combinations.size() << "\n";
	std::cout << "Number of all forms: " << forms.size() << "\n";

	while (!combinations.empty())
	{
		std::cout <<"Remaining combinations: " << combinations.size() << std::endl;
		//Calcualate the form that contributes for the maximal number of combinations
		std::map<Form, uint64_t> form2ComNumberMap;
		for (const Form& form : forms)
			form2ComNumberMap[form] = 0;
		for (const Combination& combination : combinations)
			for (const Form& form : com2FormSetMap.find(combination)->second)
				form2ComNumberMap.find(form)->second++;

		uint64_t maxCombinationNumber = 0;
		Form& bestForm = forms.front();
		for (const Form& form : forms)
		{
			auto curFormCombNumberPairIt = form2ComNumberMap.find(form);
			if (curFormCombNumberPairIt->second > maxCombinationNumber)
			{
				maxCombinationNumber = curFormCombNumberPairIt->second;
				bestForm = form;
			}
		}

		//Adding the best form the the MCS
		resultMCS.mcsForms.push_back(bestForm);

		//Removing the combinations, containing the best form form
		auto newEndIt = std::remove_if(combinations.begin(), combinations.end(),
			[&bestForm](const Combination& combination) {
				return combination.contains(bestForm);
			});
		combinations.erase(newEndIt, combinations.end());

	}

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
