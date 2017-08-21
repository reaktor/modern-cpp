#include "gtest/gtest.h"

#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>

TEST(AlgorithmsBasic, SumOfVectorElements)
{
    std::vector<int> v{ 1, 2, 3, 4, 5 };

    int sum = 0;

    ASSERT_EQ(15, sum);
}

TEST(AlgorithmsBasic, InnerProductOfVectors)
{
    std::vector<int> v1{ 1, 2, 3, 4, 5 };
    std::vector<int> v2{ 2, 2, 2, 2, 2 };

    int sum = 0;

    ASSERT_EQ(30, sum);
}

TEST(AlgorithmsBasic, PartialSumOfVectors)
{
    std::vector<int> v{ 1, 1, 1, 1, 1 };

    std::vector<int> partial_sums(v.size());

    std::vector<int> expected{ 1, 2, 3, 4, 5 };
    ASSERT_EQ(expected, partial_sums);
}

TEST(AlgorithmsBasic, CountZeroes)
{
    std::vector<int> v{ 0, 1, 2, 4, 0, 1, 2 };

    int count = 0;

    ASSERT_EQ(2, count);
}

TEST(AlgorithmsBasic, CountEvens)
{
    std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7 };

    int count = 0;

    ASSERT_EQ(3, count);
}

// Lower bound is the first element of a range that is not less than a given
// value. In this case the value is 3, and the first element that is not less
// than 3 is the third element of the vector (i.e. at index 2)
TEST(AlgorithmsBasic, LowerBound)
{
    std::vector<int> v{ 1, 1, 3, 3, 4, 5 };

    //int bound = 3;
    size_t i = 0;

    ASSERT_EQ(2, i);
}

// Upper bound is the first element of a vector that is greater than a given
// value. In this case the value is 2, and the first element greater than 2 is
// the fourth element of the vector, at index 3.
TEST(AlgorithmsBasic, UpperBound)
{
    std::vector<int> v{ 1, 1, 2, 3, 3, 3 };

    //int bound = 2;
    size_t i = 0;

    ASSERT_EQ(3, i);
}

TEST(AlgorithmsBasic, FindMaximum)
{
    std::vector<int> v{ 1, 6, 3, 8, 2, 0, 7 };

    int max = v[0];

    ASSERT_EQ(8, max);
}
