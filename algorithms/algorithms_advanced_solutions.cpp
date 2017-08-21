#include "gtest/gtest.h"

#include <algorithm>
#include <cmath>
#include <iterator>
#include <numeric>
#include <vector>

TEST(AlgorithmsAdvancedSolutions, ConvertAVectorToString)
{
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    auto s = std::accumulate(std::next(begin(v)), end(v), std::to_string(v[0]),
        [](auto& acc, auto& x) { return acc + ", " + std::to_string(x); });

    std::string result = "[" + s + "]";
    ASSERT_EQ("[1, 2, 3, 4, 5]", result);
}

TEST(AlgorithmsAdvancedSolutions, CountEqualElements)
{
    std::vector<int> a{ 1, 2, 3, 4, 5 };
    std::vector<int> b{ 10, 2, 30, 4, 50 };

    auto count = std::inner_product(begin(a), end(a), begin(b), 0,
        std::plus<int>(), std::equal_to<int>());
    ASSERT_EQ(2, count);
}

TEST(AlgorithmsAdvancedSolutions, CreateMapFromKeysAndValues)
{
    std::vector<std::string> keys{ "Helsinki", "Espoo", "Tampere", "Vantaa", "Oulu" };
    std::vector<int> values{ 639'222, 276'087, 228'942, 220'908, 200'600 };

    std::map<std::string, int> population;
    std::transform(begin(keys), end(keys), begin(values),
        std::inserter(population, begin(population)),
        [](auto k, auto v) { return std::make_pair(k, v); });

    ASSERT_EQ(5, population.size());
    ASSERT_EQ(639'222, population["Helsinki"]);
    ASSERT_EQ(200'600, population["Oulu"]);
    ASSERT_EQ(228'942, population["Tampere"]);
}

TEST(AlgorithmsAdvancedSolutions, CalculatesHeightsFromDifferences)
{
    std::vector<int> diff{ 0, 1, 5, -2, 10, -12 };

    std::vector<int> heights;
    std::partial_sum(begin(diff), end(diff), std::back_inserter(heights));

    std::vector<int> expected{ 0, 1, 6, 4, 14, 2 };
    ASSERT_EQ(expected, heights);
}

TEST(AlgorithmsAdvancedSolutions, FindMinimumOfAdjacentNumbers)
{
    std::vector<int> numbers{ 1, 2, 1, 3, 1, 4 };

    std::vector<int> minimums;
    std::adjacent_difference(begin(numbers), end(numbers),
        std::back_inserter(minimums),
        [](auto l, auto r) { return std::min(l, r); });

    std::vector<int> expected{ 1, 1, 1, 1, 1, 1 };
    ASSERT_EQ(expected, minimums);
}

TEST(AlgorithmsAdvancedSolutions, MoveMultipleElementsInAContainer)
{
    std::vector<int> numbers{ 1, 2, 3, 4, 5, 6, 7 };

    std::rotate(begin(numbers) + 1, begin(numbers) + 3, end(numbers) - 1);

    std::vector<int> expected{ 1, 4, 5, 6, 2, 3, 7 }; // [2, 3] moved near the end
    ASSERT_EQ(expected, numbers);
}

TEST(AlgorithmsAdvancedSolutions, MoveMultipleElementsToBeginningOfAContainer)
{
    std::vector<int> numbers{ 1, 2, 3, 3, 2, 4, 2, 1, 5 };

    std::stable_partition(begin(numbers), end(numbers), [](auto x) { return x == 2; });

    std::vector<int> expected{ 2, 2, 2, 1, 3, 3, 4, 1, 5 }; // 2's moved to the beginning
    ASSERT_EQ(expected, numbers);
}

TEST(AlgorithmsAdvancedSolutions, MoveMultipleElementsToEndOfAContainer)
{
    std::vector<int> numbers{ 1, 2, 3, 3, 2, 4, 2, 1, 5 };

    std::stable_partition(begin(numbers), end(numbers), [](auto x) { return x != 2; });

    std::vector<int> expected{ 1, 3, 3, 4, 1, 5, 2, 2, 2 }; // 2's moved to the end
    ASSERT_EQ(expected, numbers);
}

TEST(AlgorithmsAdvancedSolutions, CheckThatOneElementSatisfiesACondition)
{
    std::string s{ "hello, world" };

    bool has_spaces = std::any_of(begin(s), end(s), [](auto c) { return c == ' '; });

    ASSERT_EQ(true, has_spaces);
}

TEST(AlgorithmsAdvancedSolutions, CheckThatAllElementsSatisfyACondition)
{
    std::vector<int> v{ 1, 3, 5, 7, 9, 11 };

    bool all_odd = std::all_of(begin(v), end(v), [](auto n) { return n % 2 == 1; });

    ASSERT_EQ(true, all_odd);
}

TEST(AlgorithmsAdvancedSolutions, CheckThatNoElementSatisfiesCondition)
{
    std::string s{ "hello, world" };

    bool is_uppercase = std::any_of(begin(s), end(s), [](auto c) { return std::isupper(c); });

    ASSERT_EQ(false, is_uppercase);
}

TEST(AlgorithmsAdvancedSolutions, FindMinimumAndMaximumElement)
{
    std::vector<int> v{ 1, 6, 3, 7, 9, 4, 12, 2 };

    auto minmax = std::minmax_element(begin(v), end(v));

    ASSERT_EQ(1, *minmax.first);
    ASSERT_EQ(12, *minmax.second);
}

TEST(AlgorithmsAdvancedSolutions, FindZeroCrossingOfCosine)
{
    std::vector<double> c(628300);

    // Create an approximation of cosine
    std::iota(begin(c), end(c), 0);
    std::transform(begin(c), end(c), begin(c), [](auto d) { return std::cos(d / 100000.0); });

    // Find the first index where the value of cosine is less or equal to zero
    auto result = std::upper_bound(begin(c), end(c), 0.0, std::greater<double>());

    ASSERT_EQ(157080, result - begin(c));
}

TEST(AlgorithmsAdvancedSolutions, ReadNumbersFromAString)
{
    // First number tells how many numbers there are to be read
    std::string numbers{ "5 0 1 2 3 4" };
    std::istringstream is(numbers);

    size_t count;
    is >> count;
    std::vector<int> result;
    std::copy_n(std::istream_iterator<int>(is), count, std::back_inserter(result));

    std::vector<int> expected{ 0, 1, 2, 3, 4 };
    ASSERT_EQ(expected, result);
}
