#include "form.h"
#include <functional>
#include "binomFunction.h"


// Generates forms of ones and zeros in a binary sequence
// with maximal length.
// Every combination begins and ends with 1.
//
// matches: Number of ones in the binary sequence
//
// Returns: Vector of Forms objects representing all Forms
std::vector<Form> Form::generateAllForms(uint64_t length, uint64_t matches)
{
    std::vector<Form> allForms;
    uint64_t max_zeros = length - matches;
    uint64_t ones = matches;
   

    allForms.reserve(binom(length - 1, max_zeros));
    // Recursive function to generate forms
    std::function<void(uint64_t, uint64_t, kMismatchIntegerType::uint_type)> generateForms;
    generateForms = [&allForms, &generateForms]
    (uint64_t remainOnes, uint64_t remainZeros, kMismatchIntegerType::uint_type curFormInt) {
        if (!remainOnes)
            allForms.push_back(Form((curFormInt << 1) | 1));
        if (remainOnes)
            generateForms(remainOnes - 1, remainZeros, (curFormInt << 1) | 1);
        if (remainZeros)
            generateForms(remainOnes, remainZeros - 1, curFormInt << 1);
    }; 

    generateForms(ones - 2, max_zeros, 1);

    return allForms;
}
