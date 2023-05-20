#include "k_mismatch_search.h"
#include <random>
#include <numeric>
#include <execution>
#include <unordered_map>
#include <iostream>
#include <set>
KMismatchSearch::KMismatchSearch()
{
}

void KMismatchSearch::initRandomText(size_t size, size_t alphabetSize, size_t seed)
{

    this->text.clear();
    // Reserve the necessary space
    this->text.reserve(size);

    // Create a mersenne twister seeded with seed
    std::mt19937 gen(seed);

    // Create a distribution in range from 'A' to 'Z'
    std::uniform_int_distribution<size_t> dist('A', 'A' + alphabetSize - 1);

    // Generate the random text
    for (size_t i = 0; i < size; ++i)
    {
        this->text.push_back(static_cast<char>(dist(gen)));
    }
}

const std::string& KMismatchSearch::getText() const
{
    return text;
}



std::map<std::string, std::vector<size_t>> KMismatchSearch::naiveSearch(std::vector<std::string> queries, size_t maxMismatchs) const
{
    std::map<std::string, std::vector<size_t>> resultMap;
    std::mutex mtx;
    std::vector<size_t> indices(text.size());
    std::iota(indices.begin(), indices.end(), 0);

    std::for_each(std::execution::par, indices.begin(), indices.end(),
        [&](size_t i) {
            for (const auto& query : queries) {
                if (CheckQueryOnPosition(query, i, maxMismatchs)) {
                    // Lock before modifying shared data
                    std::lock_guard<std::mutex> lock(mtx);
                    resultMap[query].push_back(i);
                }
            }
        }
    );
    


    return resultMap;
}

std::map<std::string, std::set<size_t>> KMismatchSearch::mcsSearch(std::vector<std::string> queries, size_t maxMismatchs, const MCS& mcs) const
{
    std::mutex mtx;
    std::vector<size_t> indices(text.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::map<std::string, std::vector<size_t>> formMap;
    std::map<std::string, std::set<size_t>> resultMap;
    std::for_each(std::execution::par, indices.begin(), indices.end(),
        [&](size_t pos) {
            for (auto& form : mcs.getMcsForms())
            {
                if (pos + form.getSize() <= text.size())
                {
                    std::string cur_str = form.getStringFromPosition(text, pos);
                    std::lock_guard<std::mutex> lock(mtx);
                    formMap[cur_str].push_back(pos);
                }
            }
        });

    for (const auto& query : queries)
    {
        for (auto& form : mcs.getMcsForms())
        {
            for (size_t qPos = 0; qPos + form.getSize() <= query.size(); qPos++)
            {
                for (size_t pos : formMap[form.getStringFromPosition(query, qPos)])
                {
                    if (CheckQueryOnPosition(query, pos-qPos, maxMismatchs)) {
                        resultMap[query].insert(pos - qPos);
                    }
                }
            }
        }
    }
    

    return resultMap;
}

bool KMismatchSearch::CheckQueryOnPosition(const std::string& query, int64_t position, size_t maxMismatchs) const
{
    if (position + query.size() > text.size() || position < 0)
        return false;

    for (auto& ch : query)
    {
        if (ch != text[position])
        {
            if (maxMismatchs != 0){
                maxMismatchs--;
            }
            else {
                return false;
            }
        }
        position++;
    }

    return true;
}
