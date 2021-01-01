#include "dubins/Line.hpp"
#include "dubins/output.hpp"

#include <gtest/gtest.h>
#include <iostream>

TEST(LineTest, line_2d_length_a)
{
    using namespace dubins;

    Line2D a{{-1.5, -1.5}, {1.5, 2.5}};


    auto c = length(a);

    EXPECT_DOUBLE_EQ(c, 5.0);
}

TEST(LineTest, line_2d_length_sq_a)
{
    using namespace dubins;

    Line2D a{{-1.5, -1.5}, {1.5, 2.5}};

    auto c = length_sq(a);

    EXPECT_DOUBLE_EQ(c, 25.0);
}
