#include "combination.h"
#include <functional>
#include "binomFunction.h"




bool Combination::contains(const Form& form) const
{
    kMismatchIntegerType::uint_type formInt = form.sequenceInt;
    kMismatchIntegerType::uint_type combinationInt = this->sequenceInt;

    //Run until the MSB of integer type is 1
    while (!((static_cast<kMismatchIntegerType::uint_type>(1) << (kMismatchIntegerType::UINT_TYPE_SIZE - 1)) & formInt))
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
        if ((combinationInt | ~formInt) == ~static_cast<kMismatchIntegerType::uint_type>(0))
            return true;
        formInt <<= 1;
    }

    //Last check for MSB is 1
    if ((combinationInt | ~formInt) == ~static_cast<kMismatchIntegerType::uint_type>(0))
        return true;

    return false;
}

kMismatchIntegerType::uint_type cutRightZeros(kMismatchIntegerType::uint_type n)
{
    while (!(n & 1))
        n >>= 1;
    return n;
}

std::set<Form> Combination::getAllForms(uint64_t matches) const
{
    std::set<Form> allInnerForms;
    kMismatchIntegerType::uint_type combInt = this->sequenceInt;

    // Recursive function to generate combinations
    std::function<void(uint64_t, kMismatchIntegerType::uint_type, kMismatchIntegerType::uint_type)> generateInnerForms;
    generateInnerForms = [&allInnerForms, &generateInnerForms, &combInt]
       (uint64_t remainOnes, kMismatchIntegerType::uint_type curPosition, kMismatchIntegerType::uint_type curFormInt)
    {
        if (!remainOnes) {
            allInnerForms.insert(Form(cutRightZeros(curFormInt)));
            return;
        }

        while (!((static_cast<uint64_t>(1)<< (kMismatchIntegerType::UINT_TYPE_SIZE - 1)) & curPosition))
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
    std::function<void(uint64_t, uint64_t, kMismatchIntegerType::uint_type)> generateCombinations;
    generateCombinations = [&allCombinations, &generateCombinations]
    (uint64_t remainOnes, uint64_t remainZeros, kMismatchIntegerType::uint_type curCombinationInt) {
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