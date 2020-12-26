#include "dubins/Vector.hpp"

#include "gtest/gtest.h"


TEST(VectorTest, test_a_dot_b)
{
    using namespace dubins;

    Vector2D a{1.0, 2.0};
    Vector2D b{3.0, 5.0};


    auto c = inner(a, b);

    EXPECT_DOUBLE_EQ(c, 13.0);
}

TEST(VectorTest, test_a_cross_b)
{
    using namespace dubins;

    Vector2D a{1.0, 2.0};
    Vector2D b{3.0, 5.0};


    auto c = outer(a, b);

    EXPECT_DOUBLE_EQ(c, -1.0);
}


TEST(VectorTest, test_a_plus_b)
{
    using namespace dubins;

    Vector2D a{1.0, 2.0};
    Vector2D b{0.5, 1.66};

    auto c = a + b;

    EXPECT_DOUBLE_EQ(c.x, 1.5);
    EXPECT_DOUBLE_EQ(c.y, 3.66);
}

TEST(VectorTest, test_negate_a)
{
    using namespace dubins;

    Vector2D a{1.0, 2.0};
    Vector2D b{-1.0, -2.0};

    EXPECT_EQ(-a, b);
}

TEST(VectorTest, test_a_minus_b)
{
    using namespace dubins;

    Vector2D a{1.0, 2.0};
    Vector2D b{0.5, 1.66};

    auto c = a - b;

    EXPECT_DOUBLE_EQ(c.x, 0.5);
    EXPECT_DOUBLE_EQ(c.y, 0.34);
}

TEST(VectorTest, test_a_equal_b)
{
    using namespace dubins;

    Vector2D a{0.0, 1.0};
    Vector2D b{0.0, 1.0};

    EXPECT_EQ(a, b);
}

TEST(VectorTest, test_a_not_equal_b)
{
    using namespace dubins;

    Vector2D a{0.0, 0.0};
    Vector2D b{1.0, 0.0};
    Vector2D c{0.0, 1.0};
    Vector2D d{1.0, 1.0};

    EXPECT_NE(a, b);
    EXPECT_NE(a, b);
    EXPECT_NE(a, c);
    EXPECT_NE(a, d);
}
