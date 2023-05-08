#include "Combination.h"
#include <functional>
#include "binomFunction.h"




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