#include "gtest/gtest.h"

// An object that keeps tabs on its construction and destruction count
static int construct_count;
static int destruct_count;

struct tester {
    tester() { ++construct_count; }
    ~tester()
    {
        --construct_count;
        ++destruct_count;
    }

    tester(const tester& other) = delete;
    tester& operator()(const tester& other) = delete;

    void mutate() { ++mutate_count; }

    int mutate_count = 0;
};

void use_tester(tester* r)
{
    r->mutate();
}

class SmartPointers : public ::testing::Test {
protected:
    virtual void SetUp() override
    {
        construct_count = 0;
        destruct_count = 0;
    }
};

TEST_F(SmartPointers, PassingOwnerShip)
{
    {
        tester* t1 = new tester();
        t1->mutate();
        tester* t2 = t1;
        use_tester(t2);
        // Is it safe to delete t1 here?
        // Does use_tester now own the pointer or not?
    }
    ASSERT_EQ(1, construct_count);
    ASSERT_EQ(1, destruct_count);
}

TEST_F(SmartPointers, SharingOwnerShip)
{
    {
        tester* t1 = new tester();
        t1->mutate();
        tester* t2 = t1;
        use_tester(t2);

        ASSERT_EQ(2, t1->mutate_count);
        // t1 is now shared with use_tester
        // When is it safe to delete it?
    }
    ASSERT_EQ(1, construct_count);
    ASSERT_EQ(1, destruct_count);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
