#include "combination.h"
#include <functional>
#include "binomFunction.h"




bool Combination::contains(const Form& form) const
{
    uint64_t formInt = form.sequenceInt;
    uint64_t combinationInt = this->sequenceInt;
    bool last_iteration = false;
    while (true)
    {
        /*
            First is a combination, second is a forms
            (0, 0) -> 1
            (0, 1) -> 0
            (1, 0) -> 1
            (1, 1) -> 1
            NOT(NOT(combination) AND form) = combination OR NOT(form)
            we should check if we are getting all ones
        */
        if ((combinationInt | ~formInt) == ~static_cast<uint64_t>(0))
            return true;

        if (last_iteration)
            break;

        formInt <<= 1;
        // the last bit is 1, we are at the last iteration
        if (static_cast<uint64_t>(1) << 63 & formInt)
            last_iteration = true;
    }

    return false;
}

uint64_t cutRightZeros(uint64_t n)
{
    while (!(n & 1))
        n >>= 1;
    return n;
}

std::set<Form> Combination::getAllForms(uint64_t matches) const
{
    std::set<Form> allInnerForms;
    uint64_t ones = matches;
    uint64_t combInt = this->sequenceInt;

    // Recursive function to generate combinations
    std::function<void(uint64_t, uint64_t, uint64_t)> generateInnerForms;
    generateInnerForms = [&allInnerForms, &generateInnerForms, &combInt]
       (uint64_t remainOnes, uint64_t curPosition, uint64_t curFormInt) 
    {
        if (!remainOnes) {
            allInnerForms.insert(Form(cutRightZeros(curFormInt)));
            return;
        }

        while (!((static_cast<uint64_t>(1)<<63) & curPosition))
        {
            if (combInt & curPosition)
                generateInnerForms(remainOnes - 1, curPosition << 1, curFormInt | curPosition);
            curPosition <<= 1;
        }

        if ((combInt & curPosition) && (remainOnes == 1))
            allInnerForms.insert(Form(cutRightZeros(curFormInt | curPosition)));
    
    };

    generateInnerForms(matches, 1, 0);

    return allInnerForms;
}

// Generates combinations of ones and zeros in a binary sequence
// with a fixed length and a specific number of zeros (mismatchK).
// Every combination begins with 1.
//
// length: Length of the binary sequence
// mismatchK: Number of zeros in the binary sequence
//
// Returns: Vector of Combination objects representing all combinations
std::vector<Combination> Combination::generateAllCombinations(uint64_t length, uint64_t mismatchK)
{
    std::vector<Combination> allCombinations;
    uint64_t zeros = mismatchK;
    uint64_t ones = length - mismatchK;

    allCombinations.reserve(binom(length - 1, zeros));

    // Recursive function to generate combinations
    std::function<void(uint64_t, uint64_t, uint64_t)> generateCombinations;
    generateCombinations = [&allCombinations, &generateCombinations](uint64_t remainOnes, uint64_t remainZeros, uint64_t curCombinationInt) {
        if (!remainOnes && !remainZeros)
            allCombinations.push_back(Combination(curCombinationInt));
        if (remainOnes)
            generateCombinations(remainOnes - 1, remainZeros, (curCombinationInt << 1) | 1);
        if (remainZeros)
            generateCombinations(remainOnes, remainZeros - 1, curCombinationInt << 1);
    };

    generateCombinations(ones - 1, zeros, 1);

    return allCombinations;
}