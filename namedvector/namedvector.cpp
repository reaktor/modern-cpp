#include <string>

#include "gtest/gtest.h"

// Test harness
#include "name.h"

// --------------------------------
// Implement:
// - copy-constructor
// - move-constructor
// - copy assignment operator
// - move assignment operator
// - destructor
struct NamedVector {
    NamedVector() = default;
    NamedVector(Name* name, float x, float y)
        : name(Name::copy(name))
        , x(x)
        , y(y)
    {
    }

    Name* name = nullptr;
    float x = 0.f;
    float y = 0.f;
};

// --------------------------------

// Test cases below
class NamedVectorTest : public ::testing::Test {
    virtual void SetUp() override
    {
        Name::names_in_memory = 0;
    }

    virtual void TearDown() override
    {
        ASSERT_EQ(0, Name::names_in_memory);
    }
};

TEST_F(NamedVectorTest, NameIsFreedOnDelete)
{
    auto name = new Name("Foo");
    NamedVector nv{ name, 10.5f, 20.f };
    delete name;
}

TEST_F(NamedVectorTest, NameIsCopiedOnCopy)
{
    auto name = new Name("Foo");
    NamedVector nv{ name, 10.5f, 20.f };
    NamedVector nv2(nv);
    ASSERT_TRUE(&nv != &nv2);
    ASSERT_TRUE(nv.name != nv2.name);
    ASSERT_EQ(nv.name->v, nv2.name->v);
    delete name;
}

TEST_F(NamedVectorTest, NameIsCopiedOnAssignment)
{
    auto name = new Name("Foo");
    auto name2 = new Name("Bar");
    NamedVector nv{ name, 10.5f, 20.f };
    NamedVector nv2{ name2, 5.f, 2.f };
    nv2 = nv;
    ASSERT_TRUE(&nv != &nv2);
    ASSERT_TRUE(nv.name != nv2.name);
    ASSERT_EQ(nv.name->v, nv2.name->v);
    delete name;
    delete name2;
}

TEST_F(NamedVectorTest, NamedVectorIsMovable)
{
    auto name = new Name("Foo");
    NamedVector nv{ name, 10.5f, 20.f };
    NamedVector nv2 = std::move(nv);
    ASSERT_TRUE(&nv != &nv2);
    ASSERT_TRUE(nv.name != nv2.name);
    ASSERT_EQ(nv2.name->v, name->v);
    ASSERT_TRUE(nv.name == nullptr || nv.name->v != name->v);
    delete name;
}
