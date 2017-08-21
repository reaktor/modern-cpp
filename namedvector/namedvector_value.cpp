#include <string>

#include "gtest/gtest.h"

// Test harness
#include "name.h"

// Named vector with value members
struct NamedVectorValue {
    NamedVectorValue() = default;
    NamedVectorValue(const Name& name, float x, float y)
        : name(name)
        , x(x)
        , y(y)
    {
    }
    Name name;
    float x = 0.f;
    float y = 0.f;
};

// --------------------------------

// Test cases below
class NamedVectorValueTest : public ::testing::Test {
    virtual void SetUp() override
    {
        Name::names_in_memory = 0;
    }

    virtual void TearDown() override
    {
        ASSERT_EQ(0, Name::names_in_memory);
    }
};

TEST_F(NamedVectorValueTest, NameIsFreedOnDelete)
{
    Name name("Foo");
    NamedVectorValue nv{ name, 10.5f, 20.f };
}

TEST_F(NamedVectorValueTest, NameIsCopiedOnCopy)
{
    Name name("Foo");
    NamedVectorValue nv{ name, 10.5f, 20.f };
    NamedVectorValue nv2(nv);
    ASSERT_TRUE(&nv != &nv2);
    ASSERT_EQ(nv.name, nv2.name);
}

TEST_F(NamedVectorValueTest, NameIsCopiedOnAssignment)
{
    Name name("Foo");
    Name name2("Bar");
    NamedVectorValue nv{ name, 10.5f, 20.f };
    NamedVectorValue nv2{ name2, 5.f, 2.f };
    nv2 = nv;
    ASSERT_TRUE(&nv != &nv2);
    ASSERT_EQ(nv.name, nv2.name);
}

TEST_F(NamedVectorValueTest, NamedVectorIsMovable)
{
    Name name("Foo");
    NamedVectorValue nv{ name, 10.5f, 20.f };
    NamedVectorValue nv2 = std::move(nv);
    ASSERT_TRUE(&nv != &nv2);
    ASSERT_EQ(nv2.name, name);
}
