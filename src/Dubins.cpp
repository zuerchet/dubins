#include "dubins/Dubins.hpp"
#include "dubins/Angle.hpp"
#include "dubins/Circle.hpp"
#include "dubins/Line.hpp"
#include "dubins/Vector.hpp"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

#include "dubins/output.hpp"

namespace dubins
{
namespace
{
struct LeftArc
{
    CircleCCW circle{Circle{{0.0, 0.0}, 1.0}};
    Angle     start_angle{0.0};
    Angle     end_angle{0.0};
};

struct RightArc
{
    CircleCW circle{Circle{{0.0, 0.0}, 1.0}};
    Angle    start_angle{0.0};
    Angle    end_angle{0.0};
};

double arc_length(const LeftArc& arc)
{
    return arc.circle.radius * Angle::positive_difference(arc.end_angle, arc.start_angle);
}

double arc_length(const RightArc& arc)
{
    return std::abs(arc.circle.radius * Angle::negative_difference(arc.end_angle, arc.start_angle));
}

Angle get_angle_on_circle(const Vector2D& point, const Circle& circle) noexcept
{
    const auto v = point - circle.center;
    return Angle{std::atan2(v.y, v.x)};
}

double get_segments_impl(std::vector<State>& segments, const LeftArc& arc, double segment_length, double dist) noexcept
{
    const auto start_angle     = (double)arc.start_angle + dist / arc.circle.radius;    // Angle of first point
    const auto rad_per_segment = segment_length / arc.circle.radius;
    const auto max_angle       = Angle::positive_difference(arc.end_angle, arc.start_angle);

    double angle = 0.0;
    while (angle <= max_angle)
    {
        State state;
        state.position = arc.circle.center
                         + arc.circle.radius * Vector2D{std::cos(start_angle + angle), std::sin(start_angle + angle)};
        state.heading = (start_angle + angle) + M_PI_2;

        if (state.heading > M_PI)
            state.heading -= 2.0 * M_PI;

        segments.push_back(state);

        angle += rad_per_segment;
    }

    return (max_angle - (angle - rad_per_segment)) * arc.circle.radius;
}

double get_segments_impl(std::vector<State>& segments, const RightArc& arc, double segment_length, double dist) noexcept
{
    const auto start_angle     = (double)arc.start_angle - dist / arc.circle.radius;    // Angle of first point
    const auto rad_per_segment = segment_length / arc.circle.radius;
    const auto max_angle       = std::abs(Angle::negative_difference(arc.end_angle, arc.start_angle));

    double angle = 0.0;
    while (angle <= max_angle)
    {
        State state;
        state.position = arc.circle.center
                         + arc.circle.radius * Vector2D{std::cos(start_angle - angle), std::sin(start_angle - angle)};
        state.heading = (start_angle - angle) - M_PI_2;

        if (state.heading < -M_PI)
            state.heading += 2.0 * M_PI;


        segments.push_back(state);

        angle += rad_per_segment;
    }

    return (max_angle - (angle - rad_per_segment)) * arc.circle.radius;
}

double get_segments_impl(std::vector<State>& segments, const Line2D& line, double segment_length, double dist) noexcept
{
    const auto v        = line.b - line.a;
    const auto len      = norm(v);
    const auto v_norm   = v / len;
    const auto heading  = std::atan2(v.y, v.x);
    auto       distance = dist;

    while (distance <= len)
    {
        State state;
        state.position = line.a + distance * v_norm;
        state.heading  = heading;

        segments.push_back(state);

        distance += segment_length;
    }

    return len - (distance - segment_length);
}

class PathBase
{
    public:
    virtual ~PathBase() noexcept                                                 = default;
    virtual std::vector<State> get_segments(const Dubins::Options& opt) noexcept = 0;
    virtual double             get_length() noexcept                             = 0;
};

template<typename StartArc, typename EndArc>
class CSCPath : public PathBase
{
    public:
    CSCPath(const StartArc& start, const EndArc& end) noexcept : m_start{start}, m_end{end}
    {
        // Get transfor line
        auto line = calculate_transfer_line(m_start.circle, m_end.circle);

        if (line.has_value() == false)
        {
            return;
        }

        m_mid = line.value();

        // Get start and end angles
        m_start.end_angle = get_angle_on_circle(m_mid.a, m_start.circle);
        m_end.start_angle = get_angle_on_circle(m_mid.b, m_end.circle);

        // Set path length
        const auto d_start = arc_length(m_start);
        const auto d_mid   = length(m_mid);
        const auto d_end   = arc_length(m_end);

        m_length = d_start + d_mid + d_end;
    }

    std::vector<State> get_segments(const Dubins::Options& opt) noexcept final
    {
        std::vector<State> segments;

        const auto num_segments   = std::floor(m_length / opt.max_segment_length) + 1;
        const auto segment_length = m_length / std::max(double(opt.min_number_of_segments), num_segments);

        double remain = 0.0;

        remain = get_segments_impl(segments, m_start, segment_length, 0.0);
        remain = get_segments_impl(segments, m_mid, segment_length, segment_length - remain);
        remain = get_segments_impl(segments, m_end, segment_length, segment_length - remain);

        return segments;
    }

    double get_length() noexcept final { return m_length; }

    StartArc m_start;
    Line2D   m_mid;
    EndArc   m_end;
    double   m_length{std::numeric_limits<double>::infinity()};
};

template<typename StartArc, typename MidArc>
class CCCPath : public PathBase
{
    public:
    CCCPath(const StartArc& start, const StartArc& end) noexcept : m_start{start}, m_end{end}
    {
        // Get transfor circle
        auto circle =
            calculate_transfer_circle(start.circle, end.circle, 0.5 * (start.circle.radius + end.circle.radius));

        if (circle.has_value() == false)
        {
            return;
        }

        m_mid.circle = circle.value();

        // Get start and end angles
        m_start.end_angle = get_angle_on_circle(m_mid.circle.center, m_start.circle);
        m_end.start_angle = get_angle_on_circle(m_mid.circle.center, m_end.circle);

        m_mid.start_angle = get_angle_on_circle(m_start.circle.center, m_mid.circle);
        m_mid.end_angle   = get_angle_on_circle(m_end.circle.center, m_mid.circle);

        // Set path length
        const auto d_start = arc_length(m_start);
        const auto d_mid   = arc_length(m_mid);
        const auto d_end   = arc_length(m_end);

        m_length = d_start + d_mid + d_end;
    }

    std::vector<State> get_segments(const Dubins::Options& opt) noexcept final
    {
        std::vector<State> segments;

        const auto num_segments   = std::ceil(m_length / opt.max_segment_length);
        const auto segment_length = m_length / std::max(double(opt.min_number_of_segments), num_segments);

        double remain = 0.0;

        remain = get_segments_impl(segments, m_start, segment_length, 0.0);
        remain = get_segments_impl(segments, m_mid, segment_length, segment_length - remain);
        remain = get_segments_impl(segments, m_end, segment_length, segment_length - remain);

        return segments;
    }

    double get_length() noexcept final { return m_length; }

    StartArc m_start;
    MidArc   m_mid;
    StartArc m_end;
    double   m_length{std::numeric_limits<double>::infinity()};
};

// Object to initialize starting and ending circular arcs
class Arcs
{
    public:
    Arcs(const State& start, const State& end, const double radius)
    {
        const auto start_u     = Vector2D{std::cos(start.heading + M_PI_2), std::sin(start.heading + M_PI_2)};
        const auto start_left  = start.position + radius * start_u;
        const auto start_right = start.position - radius * start_u;

        m_start_left.circle.center = start_left;
        m_start_left.circle.radius = radius;
        m_start_left.start_angle   = start.heading - M_PI_2;
        m_start_left.end_angle     = m_start_left.start_angle;

        m_start_right.circle.center = start_right;
        m_start_right.circle.radius = radius;
        m_start_right.start_angle   = start.heading + M_PI_2;
        m_start_right.end_angle     = m_start_right.start_angle;

        const auto end_u     = Vector2D{std::cos(end.heading + M_PI_2), std::sin(end.heading + M_PI_2)};
        const auto end_left  = end.position + radius * end_u;
        const auto end_right = end.position - radius * end_u;
        const auto end_ang   = start.heading - M_PI_2;

        m_end_left.circle.center = end_left;
        m_end_left.circle.radius = radius;
        m_end_left.start_angle   = end.heading - M_PI_2;
        m_end_left.end_angle     = m_end_left.start_angle;

        m_end_right.circle.center = end_right;
        m_end_right.circle.radius = radius;
        m_end_right.start_angle   = end.heading + M_PI_2;
        m_end_right.end_angle     = m_end_right.start_angle;
    }

    LeftArc  m_start_left;
    RightArc m_start_right;
    LeftArc  m_end_left;
    RightArc m_end_right;
};

}    // namespace

// Object to calculate path information
class Dubins::Path
{
    public:
    Path(const State& start, const State& end, const double radius) : m_arcs(start, end, radius)
    {
        m_paths[0] = std::make_unique<CSCPath<LeftArc, LeftArc>>(m_arcs.m_start_left, m_arcs.m_end_left);
        m_paths[1] = std::make_unique<CSCPath<RightArc, RightArc>>(m_arcs.m_start_right, m_arcs.m_end_right);
        m_paths[2] = std::make_unique<CSCPath<RightArc, LeftArc>>(m_arcs.m_start_right, m_arcs.m_end_left);
        m_paths[3] = std::make_unique<CSCPath<LeftArc, RightArc>>(m_arcs.m_start_left, m_arcs.m_end_right);
        m_paths[4] = std::make_unique<CCCPath<LeftArc, RightArc>>(m_arcs.m_start_left, m_arcs.m_end_left);
        m_paths[5] = std::make_unique<CCCPath<RightArc, LeftArc>>(m_arcs.m_start_right, m_arcs.m_end_right);

        double       len = std::numeric_limits<double>::infinity();
        std::int64_t idx = 0;

        for (const auto& path : m_paths)
        {
            if (path->get_length() < len)
            {
                len   = path->get_length();
                m_idx = idx;
            }
            ++idx;
        }
    }

    double             length() noexcept { return m_paths[m_idx]->get_length(); }
    std::vector<State> segments(const Options& opt) { return m_paths[m_idx]->get_segments(opt); };

    std::vector<State> segments_idx(std::size_t idx, const Options& opt) { return m_paths[idx]->get_segments(opt); }


    private:
    Arcs                                     m_arcs;
    std::array<std::unique_ptr<PathBase>, 6> m_paths;
    std::int64_t                             m_idx{-1};
};

Dubins::Dubins(const State& start, const State& end, const Options& options) noexcept :
    pimpl{std::make_unique<Path>(start, end, options.turning_radius)}
{
}

Dubins::~Dubins() = default;

double Dubins::length() noexcept
{
    return pimpl->length();
}

std::vector<State> Dubins::segmented_path(const Options& options) noexcept
{
    return pimpl->segments(options);
}

std::vector<State> Dubins::segmented_lsl(const Options& options) noexcept
{
    return pimpl->segments_idx(0U, options);
}

std::vector<State> Dubins::segmented_rsr(const Options& options) noexcept
{
    return pimpl->segments_idx(1U, options);
}

std::vector<State> Dubins::segmented_rsl(const Options& options) noexcept
{
    return pimpl->segments_idx(2U, options);
}

std::vector<State> Dubins::segmented_lsr(const Options& options) noexcept
{
    return pimpl->segments_idx(3U, options);
}

std::vector<State> Dubins::segmented_lrl(const Options& options) noexcept
{
    return pimpl->segments_idx(4U, options);
}

std::vector<State> Dubins::segmented_rlr(const Options& options) noexcept
{
    return pimpl->segments_idx(5U, options);
}


};    // namespace dubins
