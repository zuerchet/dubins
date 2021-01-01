#include "dubins/Circle.hpp"
#include "dubins/Vector.hpp"

#include <cmath>
#include <optional>

namespace dubins
{
namespace
{
struct DeconstructedVector
{
    Vector2D u{1.0, 0.0};
    double   magnitude{1.0};
};

std::optional<DeconstructedVector> deconstruct_vector_between_centers_if_valid(const Circle& a,
                                                                               const Circle& b) noexcept
{
    // Check if this is a valid scenario
    const auto vec        = b.center - a.center;
    const auto dist_sq    = norm_sq(vec);
    const auto radii_diff = a.radius - b.radius;


    if (dist_sq <= radii_diff * radii_diff)
    {
        return std::nullopt;
    }

    // Get unit vector
    const auto dist = std::sqrt(dist_sq);
    return DeconstructedVector{vec / dist, dist};
}

std::optional<Line2D> calculate_tangent_impl(const Circle& a, const Circle& b, const double sign1 = 1.0,
                                             const double sign2 = 1.0)
{
    const auto v = deconstruct_vector_between_centers_if_valid(a, b);
    if (v.has_value() == false)
    {
        return std::nullopt;
    }

    const auto c = (a.radius - sign1 * b.radius) / v->magnitude;

    if (c * c > 1.0)
    {
        return std::nullopt;
    }

    const auto h = std::sqrt(std::max(0.0, 1.0 - c * c));

    const auto n = v->u * c + sign2 * h * perpendicular(v->u);

    return Line2D{a.center + a.radius * n, b.center + sign1 * b.radius * n};
}

std::optional<Circle> calculate_transfer_circle_impl(const Circle& a, const Circle& b, double r,
                                                     double sign = 1.0) noexcept
{
    if (inside(a, b) || inside(b, a))
    {
        return std::nullopt;
    }

    auto v    = b.center - a.center;
    auto dist = norm_sq(v);

    auto radius_ac = (a.radius + r);
    auto radius_bc = (b.radius + r);

    const auto radius_ac_sq = radius_ac * radius_ac;
    const auto radius_bc_sq = radius_bc * radius_bc;

    if (dist > radius_ac_sq + radius_bc_sq + radius_ac * radius_bc)
    {
        return std::nullopt;
    }


    const auto dist_ap = (dist + radius_ac_sq - radius_bc_sq) / (2 * dist);
    const auto dist_pc = std::sqrt(std::max(0.0, (radius_ac_sq / dist - dist_ap * dist_ap)));

    return Circle{a.center + dist_ap * v - sign * dist_pc * perpendicular(v), r};
}

};    // namespace

std::optional<Line2D> calculate_transfer_line(const CircleCW& a, const CircleCW& b) noexcept
{
    return calculate_tangent_impl(a, b, 1.0, 1.0);
}

std::optional<Line2D> calculate_transfer_line(const CircleCW& a, const CircleCCW& b) noexcept
{
    return calculate_tangent_impl(a, b, -1.0, 1.0);
}

std::optional<Line2D> calculate_transfer_line(const CircleCCW& a, const CircleCW& b) noexcept
{
    return calculate_tangent_impl(a, b, -1.0, -1.0);
}

std::optional<Line2D> calculate_transfer_line(const CircleCCW& a, const CircleCCW& b) noexcept
{
    return calculate_tangent_impl(a, b, 1.0, -1.0);
}

std::optional<CircleCCW> calculate_transfer_circle(const CircleCW& a, const CircleCW& b, double r) noexcept
{
    const auto circle_opt = calculate_transfer_circle_impl(a, b, r, 1.0);
    if (circle_opt.has_value())
    {
        return CircleCCW{circle_opt.value()};
    }
    return std::nullopt;
}

std::optional<CircleCW> calculate_transfer_circle(const CircleCCW& a, const CircleCCW& b, double r) noexcept
{
    const auto circle_opt = calculate_transfer_circle_impl(a, b, r, -1.0);
    if (circle_opt.has_value())
    {
        return CircleCW{circle_opt.value()};
    }
    return std::nullopt;
}

bool inside(const Circle& a, const Circle& b) noexcept
{
    if (a.radius < b.radius)
    {
        // b cannot be contained in a
        return false;
    }

    const auto v           = b.center - a.center;
    const auto dist_sq     = norm_sq(v);
    const auto max_dist    = a.radius - b.radius;
    const auto max_dist_sq = max_dist * max_dist;

    return dist_sq <= max_dist_sq;
}

}    // namespace dubins