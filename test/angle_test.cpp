#include "dubins/Angle.hpp"

#include <gtest/gtest.h>


TEST(AngleTest, wrapping)
{
    using namespace dubins;

    {
        Angle a{0.0};
        EXPECT_DOUBLE_EQ((double)a, 0.0);
    }
    {
        Angle a{M_PI};
        EXPECT_DOUBLE_EQ((double)a, M_PI);
    }
    {
        Angle a{-M_PI};
        EXPECT_DOUBLE_EQ((double)a, M_PI);
    }
    {
        Angle a{2.0*M_PI};
        EXPECT_DOUBLE_EQ((double)a, 0.0);
    }
    {
        Angle a{-2.0*M_PI};
        EXPECT_DOUBLE_EQ((double)a, 0.0);
    }
    {
        Angle a{-M_PI_2};
        EXPECT_DOUBLE_EQ((double)a, 3.0*M_PI_2);
    }
    {
        Angle a{-M_PI_2 - 10.0*M_PI};
        EXPECT_DOUBLE_EQ((double)a, 3.0*M_PI_2);
    }
    {
        Angle a{-M_PI_2 + 10.0*M_PI};
        EXPECT_DOUBLE_EQ((double)a, 3.0*M_PI_2);
    }
}

TEST(AngleTest, signed_difference)
{
    using namespace dubins;

    {
        Angle a{0.0};
        Angle b{0.0};

        double r = Angle::signed_difference(a, b);

        EXPECT_DOUBLE_EQ(r, 0.0);
    }
    {
        Angle a{M_PI_2};
        Angle b{0.0};

        double r = Angle::signed_difference(a, b);

        EXPECT_DOUBLE_EQ(r, M_PI_2);
    }
    {
        Angle a{-M_PI_2};
        Angle b{0.0};

        double r = Angle::signed_difference(a, b);

        EXPECT_DOUBLE_EQ(r, -M_PI_2);
    }
    {
        Angle a{-M_PI};
        Angle b{M_PI};

        double r = Angle::signed_difference(a, b);

        EXPECT_DOUBLE_EQ(r, 0.0);
    }
    {
        Angle a{-M_PI_4};
        Angle b{M_PI_4};

        double r = Angle::signed_difference(a, b);

        EXPECT_DOUBLE_EQ(r, -M_PI_2);
    }
    {
        Angle a{M_PI_4};
        Angle b{-M_PI_4};

        double r = Angle::signed_difference(a, b);

        EXPECT_DOUBLE_EQ(r, M_PI_2);
    }
}

TEST(AngleTest, positive_difference)
{
    using namespace dubins;

    {
        Angle a{0.0};
        Angle b{0.0};

        double r = Angle::positive_difference(a, b);

        EXPECT_DOUBLE_EQ(r, 0.0);
    }
    {
        Angle a{M_PI_2};
        Angle b{0.0};

        double r = Angle::positive_difference(a, b);

        EXPECT_DOUBLE_EQ(r, M_PI_2);
    }
    {
        Angle a{-M_PI_2};
        Angle b{0.0};

        double r = Angle::positive_difference(a, b);

        EXPECT_DOUBLE_EQ(r, 3.0*M_PI_2);
    }
    {
        Angle a{-M_PI};
        Angle b{M_PI};

        double r = Angle::positive_difference(a, b);

        EXPECT_DOUBLE_EQ(r, 0.0);
    }
    {
        Angle a{-M_PI_4};
        Angle b{M_PI_4};

        double r = Angle::positive_difference(a, b);

        EXPECT_DOUBLE_EQ(r, 3.0*M_PI_2);
    }
    {
        Angle a{M_PI_4};
        Angle b{-M_PI_4};

        double r = Angle::positive_difference(a, b);

        EXPECT_DOUBLE_EQ(r, M_PI_2);
    }
}


TEST(AngleTest, negative_difference)
{
    using namespace dubins;

    {
        Angle a{0.0};
        Angle b{0.0};

        double r = Angle::negative_difference(a, b);

        EXPECT_DOUBLE_EQ(r, 0.0);
    }
    {
        Angle a{M_PI_2};
        Angle b{0.0};

        double r = Angle::negative_difference(a, b);

        EXPECT_DOUBLE_EQ(r, -3.0*M_PI_2);
    }
    {
        Angle a{-M_PI_2};
        Angle b{0.0};

        double r = Angle::negative_difference(a, b);

        EXPECT_DOUBLE_EQ(r, -M_PI_2);
    }
    {
        Angle a{-M_PI};
        Angle b{M_PI};

        double r = Angle::negative_difference(a, b);

        EXPECT_DOUBLE_EQ(r, 0.0);
    }
    {
        Angle a{-M_PI_4};
        Angle b{M_PI_4};

        double r = Angle::negative_difference(a, b);

        EXPECT_DOUBLE_EQ(r, -M_PI_2);
    }
    {
        Angle a{M_PI_4};
        Angle b{-M_PI_4};

        double r = Angle::negative_difference(a, b);

        EXPECT_DOUBLE_EQ(r, -3.0*M_PI_2);
    }
}