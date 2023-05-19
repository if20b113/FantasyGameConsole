#include <gtest/gtest.h>
#include "FGE/Engine.h"

TEST(sampletests, t1)
{
    EXPECT_EQ(1 + 5, 6);
}

TEST(sampletests, t2)
{
    EXPECT_EQ(2 + 2, 4);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}