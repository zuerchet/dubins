#include "dubins/Dubins.hpp"

#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <limits>
#include <vector>

#include "dubins/output.hpp"


void test_segments(const std::vector<dubins::State>& segments, const dubins::State& start, const dubins::State& end)
{
    // Check that segments are evenly distributed
    double min = std::numeric_limits<double>::infinity();
    double max = 0.0;
    double avg = 0.0;
    double sum = 0.0;

    for (auto j = 0; j < segments.size() - 1; j++)
    {
        const auto dist = norm(segments[j + 1].position - segments[j].position);
        if (dist < min)
            min = dist;

        if (dist > max)
            max = dist;

        avg = (avg * (double)j + dist) / (double)(j + 1);
        sum += dist;

        std::cout << segments[j].position << ", " << segments[j].heading << '\n';
    }

    EXPECT_NEAR(max, min, 0.0001);
    EXPECT_NEAR(max, avg, 0.0001);

    EXPECT_NEAR(segments.front().position.x, start.position.x, 1e-13);
    EXPECT_NEAR(segments.front().position.y, start.position.y, 1e-13);
    EXPECT_NEAR(segments.front().heading, start.heading, 1e-13);

    EXPECT_NEAR(segments.back().position.x, end.position.x, 1e-13);
    EXPECT_NEAR(segments.back().position.y, end.position.y, 1e-13);
    EXPECT_NEAR(segments.back().heading, end.heading, 1e-13);

    // std::cout << "Start: " << segments.front().position << ", " << segments.front().heading << '\n';
    // std::cout << "End: " << segments.back().position << ", " << segments.back().heading << '\n';
    // std::cout << "Num segments: " << segments.size() << '\n';
    // std::cout << "Max: " << max << " Min: " << min << " Average: " << avg << " Sum: " << sum << '\n';
}

TEST(DubinsTest, rsr)
{
    using namespace dubins;

    State start{{0.0, 0.0}, M_PI_2};
    State end{{5.0, 0.0}, -M_PI_2};

    Dubins::Options opt;
    opt.turning_radius         = 2.0;
    opt.max_segment_length     = 0.1;
    opt.min_number_of_segments = 20;

    Dubins     path{start, end, opt};
    const auto segments = path.segmented_path(opt);

    EXPECT_DOUBLE_EQ(path.length(), M_PI*opt.turning_radius+1.0);
    test_segments(segments, start, end);
}

TEST(DubinsTest, lsl)
{
    using namespace dubins;

    State start{{0.0, 0.0}, -M_PI_2};
    State end{{5.0, 0.0}, M_PI_2};

    Dubins::Options opt;
    opt.turning_radius         = 2.0;
    opt.max_segment_length     = 0.1;
    opt.min_number_of_segments = 20;

    Dubins     path{start, end, opt};
    const auto segments = path.segmented_path(opt);

    EXPECT_DOUBLE_EQ(path.length(), M_PI*opt.turning_radius+1.0);
    test_segments(segments, start, end);
}

TEST(DubinsTest, rsl)
{
    using namespace dubins;

    State start{{0.0, 0.0}, M_PI_2};
    State end{{4.0, 4.0}, M_PI_2};

    Dubins::Options opt;
    opt.turning_radius         = 2.0;
    opt.max_segment_length     = 0.1;
    opt.min_number_of_segments = 20;

    Dubins     path{start, end, opt};
    const auto segments = path.segmented_path(opt);

    EXPECT_DOUBLE_EQ(path.length(), M_PI*opt.turning_radius);
    test_segments(segments, start, end);
}

TEST(DubinsTest, lsr)
{
    using namespace dubins;

    State start{{0.0, 0.0}, M_PI_2};
    State end{{-4.0, 4.0}, M_PI_2};

    Dubins::Options opt;
    opt.turning_radius         = 2.0;
    opt.max_segment_length     = 0.1;
    opt.min_number_of_segments = 20;

    Dubins     path{start, end, opt};
    const auto segments = path.segmented_path(opt);

    EXPECT_DOUBLE_EQ(path.length(), M_PI*opt.turning_radius);
    test_segments(segments, start, end);
}