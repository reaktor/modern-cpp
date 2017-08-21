#include "gtest/gtest.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

// A unary functor that squares its argument
struct square {
    int operator()(const int& x) { return x * x; }
};

// A unary functor that adds 'n' to every number it sees
struct plus_n {
    plus_n(int n)
        : n(n)
    {
    }
    int operator()(const int& x) { return x + n; }

private:
    int n;
};

// A unary functor that keeps a running sum of its arguments
struct accumulator {
    void operator()(const int& x) { sum += x; }
    int total() const { return sum; }

private:
    int sum = 0;
};

// A simple higher-order function
template <typename T, typename U>
T apply_std_function(std::function<T(U)> f, U arg) { return f(arg); }

// A Simple higher-order function, with return type deduction
// Requires C++14
template <typename F, typename U>
auto apply_lambda(F f, U arg) { return f(arg); }
// In C++11: auto apply_lambda(F f, U arg) -> decltype(f(arg))

// A call to higher-order function that doesn't require any state
TEST(Lambda, UsingSimpleClosure)
{
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    std::vector<int> result;

    std::transform(begin(v), end(v), back_inserter(result), square());

    std::vector<int> expected{ 1, 4, 9, 16, 25 };
    ASSERT_EQ(expected, result);
}

// A call to higher-order function that maintains constant state across invocations
TEST(Lambda, UsingClosureToRememberState)
{
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    std::vector<int> result;

    std::transform(begin(v), end(v), back_inserter(result), plus_n(2));

    std::vector<int> expected{ 3, 4, 5, 6, 7 };
    ASSERT_EQ(expected, result);
}

// A call to higher-order function that maintains mutable state across invocations
TEST(Lambda, UsingClosureToUpdateState)
{
    std::vector<int> v{ 1, 2, 3, 4, 5 };

    accumulator acc = std::for_each(begin(v), end(v), accumulator());

    ASSERT_EQ(15, acc.total());
}

// Passing lambdas as function arguments
TEST(Lambda, PassingAsAFunctionArgument)
{
    auto f = [](int x) { return x + 1.0; };
    int result = apply_std_function<double, int>(f, 1);
    ASSERT_EQ(2.0, result);

    result = apply_lambda(f, 1);
    ASSERT_EQ(2.0, result);
}

// Lambda argument types can be deduced in C++14
TEST(Lambda, ArgumentTypeDeduction)
{
    std::vector<std::pair<int, double>> v{ { 1, 2.0 }, { 2, 3.0 } };
    std::vector<double> result;
    std::transform(begin(v), end(v), back_inserter(result), [](auto p) {
        return p.first * p.second;
    });

    std::vector<double> expected{ 2.0, 6.0 };
    ASSERT_EQ(expected, result);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
