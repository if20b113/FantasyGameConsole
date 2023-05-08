#include <gtest/gtest.h>
#include "FantasyGameEngine/FantasyGameEngine.hpp"

TEST(sampletests, t1)
{
    EXPECT_EQ(FGE::add(1, 5), 6);
}

TEST(sampletests, t2)
{
    EXPECT_EQ(FGE::add(2, 2), 4);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}