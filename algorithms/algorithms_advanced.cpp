#include "gtest/gtest.h"

#include <algorithm>
#include <cmath>
#include <iterator>
#include <numeric>
#include <vector>

TEST(AlgorithmsAdvanced, ConvertAVectorToString)
{
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    std::string s = "" + std::to_string(v[0]);

    for (size_t i = 1; i < v.size(); ++i) {
        s += ", " + std::to_string(v[i]);
    }
    std::string result = "[" + s + "]";

    ASSERT_EQ("[1, 2, 3, 4, 5]", result);
}

TEST(AlgorithmsAdvanced, CountEqualElements)
{
    std::vector<int> a{ 1, 2, 3, 4, 5 };
    std::vector<int> b{ 10, 2, 30, 4, 50 };

    int count = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] == b[i]) {
            ++count;
        }
    }

    ASSERT_EQ(2, count);
}

TEST(AlgorithmsAdvanced, CreateMapFromKeysAndValues)
{
    std::vector<std::string> keys{ "Helsinki", "Espoo", "Tampere", "Vantaa", "Oulu" };
    std::vector<int> values{ 639'222, 276'087, 228'942, 220'908, 200'600 };

    std::map<std::string, int> population;
    for (size_t i = 0; i < keys.size(); ++i) {
        population[keys[i]] = values[i];
    }

    ASSERT_EQ(5, population.size());
    ASSERT_EQ(639'222, population["Helsinki"]);
    ASSERT_EQ(200'600, population["Oulu"]);
    ASSERT_EQ(228'942, population["Tampere"]);
}

TEST(AlgorithmsAdvanced, CalculatesHeightsFromDifferences)
{
    std::vector<int> diff{ 0, 1, 5, -2, 10, -12 };

    std::vector<int> heights(diff.size());
    int cumulative = diff[0];
    heights[0] = cumulative;
    for (size_t i = 1; i < diff.size(); ++i) {
        cumulative += diff[i];
        heights[i] = cumulative;
    }

    std::vector<int> expected{ 0, 1, 6, 4, 14, 2 };
    ASSERT_EQ(expected, heights);
}

TEST(AlgorithmsAdvanced, FindMinimumOfAdjacentNumbers)
{
    std::vector<int> numbers{ 1, 2, 1, 3, 1, 4 };

    std::vector<int> minimums(numbers.size());
    minimums[0] = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        if (numbers[i - 1] < numbers[i])
            minimums[i] = numbers[i - 1];
        else
            minimums[i] = numbers[i];
    }

    std::vector<int> expected{ 1, 1, 1, 1, 1, 1 };
    ASSERT_EQ(expected, minimums);
}

TEST(AlgorithmsAdvanced, MoveMultipleElementsInAContainer)
{
    std::vector<int> numbers{ 1, 2, 3, 4, 5, 6, 7 };

    size_t first = 1;
    size_t n_first = 3;
    size_t last = numbers.size() - 1;

    std::vector<int> result;
    result.reserve(numbers.size());
    size_t i = 0;
    for (; i < first; ++i) {
        result.push_back(numbers[i]);
    }
    for (i = n_first; i < last; ++i) {
        result.push_back(numbers[i]);
    }
    for (i = first; i < n_first; ++i) {
        result.push_back(numbers[i]);
    }
    for (i = result.size(); i < numbers.size(); ++i) {
        result.push_back(numbers[i]);
    }

    std::vector<int> expected{ 1, 4, 5, 6, 2, 3, 7 }; // [2, 3] moved near the end
    ASSERT_EQ(expected, result);
}

/*
 * Create a new vector values where pred(v) == true is moved to beginning
 * Moving is stable
 */
template <typename T, class UnaryPredicate>
std::vector<T> move_to_begin_if_predicate(const std::vector<T>& vals, UnaryPredicate pred)
{
    std::vector<T> result;
    size_t last_move = 0;
    for (size_t i = 0; i < vals.size(); ++i) {
        if (pred(vals[i])) {
            result.insert(begin(result) + last_move, vals[i]);
            ++last_move;
        } else {
            result.push_back(vals[i]);
        }
    }
    return result;
}

TEST(AlgorithmsAdvanced, MoveMultipleElementsToBeginningOfAContainer)
{
    std::vector<int> numbers{ 1, 2, 3, 3, 2, 4, 2, 1, 5 };

    numbers = move_to_begin_if_predicate(numbers, [](int x) { return x == 2; });

    std::vector<int> expected{ 2, 2, 2, 1, 3, 3, 4, 1, 5 }; // 2's moved to the beginning
    ASSERT_EQ(expected, numbers);
}

TEST(AlgorithmsAdvanced, MoveMultipleElementsToEndOfAContainer)
{
    std::vector<int> numbers{ 1, 2, 3, 3, 2, 4, 2, 1, 5 };

    numbers = move_to_begin_if_predicate(numbers, [](int x) { return x != 2; });

    std::vector<int> expected{ 1, 3, 3, 4, 1, 5, 2, 2, 2 }; // 2's moved to the end
    ASSERT_EQ(expected, numbers);
}

TEST(AlgorithmsAdvanced, CheckThatOneElementSatisfiesACondition)
{
    std::string s{ "hello, world" };

    bool has_spaces = false;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == ' ') {
            has_spaces = true;
        }
    }

    ASSERT_EQ(true, has_spaces);
}

TEST(AlgorithmsAdvanced, CheckThatAllElementsSatisfyACondition)
{
    std::vector<int> v{ 1, 3, 5, 7, 9, 11 };

    bool all_odd = true;
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] % 2 == 0) {
            all_odd = false;
        }
    }

    ASSERT_EQ(true, all_odd);
}

TEST(AlgorithmsAdvanced, CheckThatNoElementSatisfiesCondition)
{
    std::string s{ "hello, world" };

    bool is_uppercase = false;
    for (size_t i = 0; i < s.size(); ++i) {
        if (std::isupper(s[i])) {
            is_uppercase = true;
        }
    }

    ASSERT_EQ(false, is_uppercase);
}

TEST(AlgorithmsAdvanced, FindMinimumAndMaximumElement)
{
    std::vector<int> v{ 1, 6, 3, 7, 9, 4, 12, 2 };

    int min = v[0];
    for (size_t i = 1; i < v.size(); ++i) {
        if (v[i] < min) {
            min = v[i];
        }
    }

    int max = v[0];
    for (size_t i = 1; i < v.size(); ++i) {
        if (max < v[i]) {
            max = v[i];
        }
    }

    ASSERT_EQ(1, min);
    ASSERT_EQ(12, max);
}

TEST(AlgorithmsAdvanced, FindZeroCrossingOfCosine)
{
    std::vector<double> c(628300);
    size_t i;

    // Create an approximation of cosine
    for (i = 0; i < c.size(); ++i) {
        c[i] = i;
    }

    for (i = 0; i < c.size(); ++i) {
        c[i] = std::cos(c[i] / 100000.0);
    }

    // Find the first index where the value of cosine is less or equal to zero
    for (i = 0; i < c.size(); ++i) {
        if (c[i] <= 0)
            break;
    }

    ASSERT_EQ(157080, i);
}

TEST(AlgorithmsAdvanced, ReadNumbersFromAString)
{
    // First number tells how many numbers there are to be read
    std::string numbers{ "5 0 1 2 3 4" };
    std::istringstream is(numbers);

    size_t count;
    is >> count;

    std::vector<int> result;
    for (size_t i = 0; i < count; ++i) {
        int n;
        is >> n;
        result.push_back(n);
    }

    std::vector<int> expected{ 0, 1, 2, 3, 4 };
    ASSERT_EQ(expected, result);
}
