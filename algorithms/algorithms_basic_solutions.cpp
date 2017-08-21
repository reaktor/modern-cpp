#include "gtest/gtest.h"

#include <algorithm>
#include <cmath>
#include <iterator>
#include <numeric>
#include <vector>

TEST(AlgorithmsBasicSolutions, SumOfVectorElements)
{
    std::vector<int> v{ 1, 2, 3, 4, 5 };

    int sum = std::accumulate(begin(v), end(v), 0);

    ASSERT_EQ(15, sum);
}

TEST(AlgorithmsBasicSolutions, InnerProductOfVectors)
{
    std::vector<int> v1{ 1, 2, 3, 4, 5 };
    std::vector<int> v2{ 2, 2, 2, 2, 2 };

    int sum = std::inner_product(begin(v1), end(v1), begin(v2), 0);

    ASSERT_EQ(30, sum);
}

TEST(AlgorithmsBasicSolutions, PartialSumOfVectors)
{
    std::vector<int> v{ 1, 1, 1, 1, 1 };

    std::vector<int> partial_sums;
    std::partial_sum(begin(v), end(v), std::back_inserter(partial_sums));

    std::vector<int> expected{ 1, 2, 3, 4, 5 };
    ASSERT_EQ(expected, partial_sums);
}

TEST(AlgorithmsBasicSolutions, CountZeroes)
{
    std::vector<int> v{ 0, 1, 2, 4, 0, 1, 2 };

    int count = std::count(begin(v), end(v), 0);

    ASSERT_EQ(2, count);
}

TEST(AlgorithmsBasicSolutions, CountEvens)
{
    std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7 };

    int count = std::count_if(begin(v), end(v), [](auto n) {
        return n % 2 == 0;
    });

    ASSERT_EQ(3, count);
}

TEST(AlgorithmsBasicSolutions, LowerBound)
{
    std::vector<int> v{ 1, 1, 2, 3, 3, 3 };

    auto result = std::lower_bound(begin(v), end(v), 2);

    ASSERT_EQ(2, result - begin(v));
}

TEST(AlgorithmsBasicSolutions, UpperBound)
{
    std::vector<int> v{ 1, 1, 2, 3, 3, 3 };

    auto result = std::upper_bound(begin(v), end(v), 2);

    ASSERT_EQ(3, result - begin(v));
}

TEST(AlgorithmsBasicSolutions, FindMaximum)
{
    std::vector<int> v{ 1, 6, 3, 8, 2, 0, 7 };

    auto max = *std::max_element(begin(v), end(v));

    ASSERT_EQ(8, max);
}
