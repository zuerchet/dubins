#include "dubins/Vector.hpp"

#include <gtest/gtest.h>

TEST(VectorTest, vec_2d_norm_a)
{
    using namespace dubins;

    Vector2D a{3.0, 4.0};


    auto c = norm(a);

    EXPECT_DOUBLE_EQ(c, 5.0);
}

TEST(VectorTest, vec_2d_norm_sq_a)
{
    using namespace dubins;

    Vector2D a{3.0, 4.0};


    auto c = norm_sq(a);

    EXPECT_DOUBLE_EQ(c, 25.0);
}

TEST(VectorTest, vec_2d_normalize_a)
{
    using namespace dubins;

    Vector2D a{2.0, 0.0};
    auto b = normalize(a);

    EXPECT_DOUBLE_EQ(b.x, 1.0);
    EXPECT_DOUBLE_EQ(b.y, 0.0);
}

TEST(VectorTest, vec_2d_a_dot_b)
{
    using namespace dubins;

    Vector2D a{1.0, 2.0};
    Vector2D b{3.0, 5.0};


    auto c = inner(a, b);

    EXPECT_DOUBLE_EQ(c, 13.0);
}

TEST(VectorTest, vec_2d_a_cross_b)
{
    using namespace dubins;

    Vector2D a{1.0, 2.0};
    Vector2D b{3.0, 5.0};


    auto c = outer(a, b);

    EXPECT_DOUBLE_EQ(c, -1.0);
}


TEST(VectorTest, vec_2d_a_plus_b)
{
    using namespace dubins;

    Vector2D a{1.0, 2.0};
    Vector2D b{0.5, 1.66};

    auto c = a + b;

    EXPECT_DOUBLE_EQ(c.x, 1.5);
    EXPECT_DOUBLE_EQ(c.y, 3.66);
}

TEST(VectorTest, vec_2d_negate_a)
{
    using namespace dubins;

    Vector2D a{1.0, 2.0};

    auto c = -a;

    EXPECT_DOUBLE_EQ(c.x, -1.0);
    EXPECT_DOUBLE_EQ(c.y, -2.0);
}

TEST(VectorTest, vec_2d_a_minus_b)
{
    using namespace dubins;

    Vector2D a{1.0, 2.0};
    Vector2D b{0.5, 1.66};

    auto c = a - b;

    EXPECT_DOUBLE_EQ(c.x, 0.5);
    EXPECT_DOUBLE_EQ(c.y, 0.34);
}

TEST(VectorTest, vec_2d_a_scalar_times_b_vec)
{
    using namespace dubins;

    double   a = 2.0;
    Vector2D b{1.0, 2.0};

    auto c = a * b;

    EXPECT_DOUBLE_EQ(c.x, 2.0);
    EXPECT_DOUBLE_EQ(c.y, 4.0);
}

TEST(VectorTest, vec_2d_a_vec_times_b_scalar)
{
    using namespace dubins;

    Vector2D a{1.0, 2.0};
    double   b = 2.0;

    auto c = a * b;

    EXPECT_DOUBLE_EQ(c.x, 2.0);
    EXPECT_DOUBLE_EQ(c.y, 4.0);
}

TEST(VectorTest, vec_2d_a_vec_divide_b_scalar)
{
    using namespace dubins;

    Vector2D a{1.0, 2.0};
    double   b = 2.0;

    auto c = a / b;

    EXPECT_DOUBLE_EQ(c.x, 0.5);
    EXPECT_DOUBLE_EQ(c.y, 1.0);
}


TEST(VectorTest, vec_2d_perpendicular_a)
{
    using namespace dubins;

    Vector2D a{1.0, 2.0};
    auto b = perpendicular(a);

    auto c = normalize(a);
    auto d = normalize(b);
    auto e = inner(c,d);

    EXPECT_DOUBLE_EQ(e, 0.0);
}
