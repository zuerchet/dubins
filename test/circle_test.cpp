#include "dubins/Circle.hpp"

#include "gtest/gtest.h"

TEST(CircleTest, test_a_equal_b)
{
    using namespace dubins;

    Circle a{{0.0, 0.0}, 1.0};
    Circle b{{0.0, 0.0}, 1.0};

    EXPECT_EQ(a, b);
}

TEST(CircleTest, test_a_not_equal_b)
{
    using namespace dubins;

    Circle a{{0.0, 0.0}, 0.0};
    Circle b{{2.0, 0.0}, 0.0};
    Circle c{{0.0, 0.0}, 1.0};
    Circle d{{2.0, 0.0}, 1.0};

    EXPECT_NE(a, b);
    EXPECT_NE(a, c);
    EXPECT_NE(a, d);
}
