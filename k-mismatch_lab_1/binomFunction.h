#pragma once
constexpr inline size_t binom(size_t n, size_t k) noexcept
{
    if (k > n)
        return 0; // out of range
    if (k == 0 || k == n)
        return 1; // edge

    return (binom(n - 1, k - 1) * n) / k;
}