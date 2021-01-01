#include "dubins/Circle.hpp"
#include "dubins/Vector.hpp"

#include <gtest/gtest.h>


TEST(CircleTest, circle_cw_cw_tangent)
{
    using namespace dubins;

    CircleCW a{Circle{{0.0, 0.0}, 3.0}};
    CircleCW b{Circle{{10.0, 0.0}, 3.0}};


    auto c = calculate_transfer_line(a, b);

    ASSERT_TRUE(c.has_value());

    // Check that the solution is valid.
    auto r1 = c->a - a.center;
    auto r2 = c->b - b.center;
    auto v  = c->b - c->a;

    // Check that the points are on the circle
    EXPECT_DOUBLE_EQ(norm(r1), a.radius);
    EXPECT_DOUBLE_EQ(norm(r2), b.radius);

    // Check that the points are tangent to the radius
    EXPECT_DOUBLE_EQ(inner(r1, v), 0.0);
    EXPECT_DOUBLE_EQ(inner(r2, v), 0.0);

    // Check that the directions are correct
    EXPECT_DOUBLE_EQ(outer(r1, v) / (norm(r1) * norm(v)), -1.0);
    EXPECT_DOUBLE_EQ(outer(r2, v) / (norm(r2) * norm(v)), -1.0);
}

TEST(CircleTest, circle_cw_ccw_tangent)
{
    using namespace dubins;

    CircleCW  a{Circle{{0.0, 0.0}, 3.0}};
    CircleCCW b{Circle{{10.0, 0.0}, 3.0}};

    auto c = calculate_transfer_line(a, b);

    ASSERT_TRUE(c.has_value());

    // Check that the solution is valid.
    auto r1 = c->a - a.center;
    auto r2 = c->b - b.center;
    auto v  = c->b - c->a;

    // Check that the points are on the circle
    EXPECT_DOUBLE_EQ(norm(r1), a.radius);
    EXPECT_DOUBLE_EQ(norm(r2), b.radius);

    // Check that the points are tangent to the radius
    EXPECT_NEAR(inner(r1, v), 0.0, 1.0e-14);
    EXPECT_NEAR(inner(r2, v), 0.0, 1.0e-14);

    // Check that the directions are correct
    EXPECT_DOUBLE_EQ(outer(r1, v) / (norm(r1) * norm(v)), -1.0);
    EXPECT_DOUBLE_EQ(outer(r2, v) / (norm(r2) * norm(v)), 1.0);
}

TEST(CircleTest, circle_ccw_cw_tangent)
{
    using namespace dubins;

    CircleCCW a{Circle{{0.0, 0.0}, 3.0}};
    CircleCW  b{Circle{{10.0, 0.0}, 3.0}};

    auto c = calculate_transfer_line(a, b);

    ASSERT_TRUE(c.has_value());
    // Check that the solution is valid.
    auto r1 = c->a - a.center;
    auto r2 = c->b - b.center;
    auto v  = c->b - c->a;

    // Check that the points are on the circle
    EXPECT_DOUBLE_EQ(norm(r1), a.radius);
    EXPECT_DOUBLE_EQ(norm(r2), b.radius);

    // Check that the points are tangent to the radius
    EXPECT_NEAR(inner(r1, v), 0.0, 1.0e-14);
    EXPECT_NEAR(inner(r2, v), 0.0, 1.0e-14);

    // Check that the directions are correct
    EXPECT_DOUBLE_EQ(outer(r1, v) / (norm(r1) * norm(v)), 1.0);
    EXPECT_DOUBLE_EQ(outer(r2, v) / (norm(r2) * norm(v)), -1.0);
}

TEST(CircleTest, circle_ccw_ccw_tangent)
{
    using namespace dubins;

    CircleCCW a{Circle{{0.0, 0.0}, 3.0}};
    CircleCCW b{Circle{{10.0, 0.0}, 3.0}};

    auto c = calculate_transfer_line(a, b);

    ASSERT_TRUE(c.has_value());
    // Check that the solution is valid.
    auto r1 = c->a - a.center;
    auto r2 = c->b - b.center;
    auto v  = c->b - c->a;

    // Check that the points are on the circle
    EXPECT_DOUBLE_EQ(norm(r1), a.radius);
    EXPECT_DOUBLE_EQ(norm(r2), b.radius);

    // Check that the points are tangent to the radius
    EXPECT_DOUBLE_EQ(inner(r1, v), 0.0);
    EXPECT_DOUBLE_EQ(inner(r2, v), 0.0);

    // Check that the directions are correct
    EXPECT_DOUBLE_EQ(outer(r1, v) / (norm(r1) * norm(v)), 1.0);
    EXPECT_DOUBLE_EQ(outer(r2, v) / (norm(r2) * norm(v)), 1.0);
}

TEST(CircleTest, circle_cw_cw_transfer_circle)
{
    using namespace dubins;

    // Overkill but test everywhere
    auto dist  = 1.0000000001;
    auto angle = 0.0;
    while (angle < 6.28)
    {
        while (dist < 5.0)
        {
            CircleCW a{Circle{{0.0, 0.0}, 3.0}};
            auto     bcenter = a.center + Vector2D{dist * std::cos(angle), dist * std::sin(angle)};
            CircleCW b{Circle{bcenter, 2.0}};
            auto     c = calculate_transfer_circle(a, b, 3.0);

            ASSERT_TRUE(c.has_value());
            // Check that the solution is valid.
            auto r1 = c->center - a.center;
            auto r2 = c->center - b.center;
            auto v  = b.center - a.center;

            // Check that the circle is the right distance away
            EXPECT_DOUBLE_EQ(norm(r1), a.radius + c->radius);
            EXPECT_DOUBLE_EQ(norm(r2), b.radius + c->radius);

            // Check circle is on the right side
            auto proj_u_v = inner(r1, v) / norm_sq(v) * v;
            auto perp     = r1 - proj_u_v;

            EXPECT_NEAR(outer(normalize(v), normalize(perp)), -1.0, 1e-8);

            dist += 0.1123;
        }
        angle += 0.1123;
    }
}

TEST(CircleTest, circle_ccw_ccw_transfer_circle)
{
    using namespace dubins;

    auto dist  = 1.000000001;
    auto angle = 0.0;
    while (angle < 6.28)
    {
        while (dist < 5.0)
        {
            CircleCCW a{Circle{{0.0, 0.0}, 3.0}};
            auto      bcenter = a.center + Vector2D{dist * std::cos(angle), dist * std::sin(angle)};
            CircleCCW b{Circle{bcenter, 2.0}};
            auto      c = calculate_transfer_circle(a, b, 3.0);

            ASSERT_TRUE(c.has_value());
            // Check that the solution is valid.
            auto r1 = c->center - a.center;
            auto r2 = c->center - b.center;
            auto v  = b.center - a.center;

            // Check that the circle is the right distance away
            EXPECT_DOUBLE_EQ(norm(r1), a.radius + c->radius);
            EXPECT_DOUBLE_EQ(norm(r2), b.radius + c->radius);

            // Check circle is on the right side
            auto proj_u_v = inner(r1, v) / norm_sq(v) * v;
            auto perp     = r1 - proj_u_v;

            EXPECT_NEAR(outer(normalize(v), normalize(perp)), 1.0, 1e-8);

            dist += 0.1123;
        }
        angle += 0.1123;
    }
}

TEST(CircleTest, circle_b_inside_a)
{
    using namespace dubins;

    Circle a{{0.0, 0.0}, 1.5};
    EXPECT_TRUE(inside(a, a));

    Circle b{{0.0, 0.0}, 1.0};
    EXPECT_TRUE(inside(a, b));

    b = Circle{{0.5, 0.0}, 1.0};
    EXPECT_TRUE(inside(a, b));

    b = Circle{{0.75, 0.0}, 1.0};
    EXPECT_FALSE(inside(a, b));

    b = Circle{{0.50001, 0.0}, 1.0};
    EXPECT_FALSE(inside(a, b));
}