#ifndef DUBINS_CIRCLE_HPP
#define DUBINS_CIRCLE_HPP

#include "dubins/Line.hpp"
#include "dubins/Vector.hpp"

#include <optional>

namespace dubins
{
/// @brief Object representing a circle
struct Circle
{
    using Point = Vector2D;    ///< Alias for a point
    Point  center;             ///< Center of the circle
    double radius{0.0};        ///< Radius of the circle
};

/// @brief Type representing a clockwise circle
struct CircleCW : public Circle
{
    explicit CircleCW(const Circle& a) : Circle(a) {}
};

/// @brief Type representing a counter-clockwise circle
struct CircleCCW : public Circle
{
    explicit CircleCCW(const Circle& a) : Circle(a) {}
};

/// @brief Find tangent line between directed circles. Line returned is the line of continous travel from circle a to
/// circle b
/// @param a starting circle
/// @param b ending circle
/// @return Tangent line transfering between circles, or empty if one does not exist or if it is not unique.
///@{
std::optional<Line2D> calculate_transfer_line(const CircleCW& a, const CircleCW& b) noexcept;
std::optional<Line2D> calculate_transfer_line(const CircleCW& a, const CircleCCW& b) noexcept;
std::optional<Line2D> calculate_transfer_line(const CircleCCW& a, const CircleCW& b) noexcept;
std::optional<Line2D> calculate_transfer_line(const CircleCCW& a, const CircleCCW& b) noexcept;
///@}


/// @brief Find a transfer circle to transition from circle a to circle be. Transfer circle will be tangent to a & b
/// @param a starting circle
/// @param b ending circle
/// @param r radius of transfer circle
/// @return Transfer circle, or empty if one does not exist or if it is not unique.
///@{
std::optional<CircleCCW> calculate_transfer_circle(const CircleCW& a, const CircleCW& b, double r) noexcept;
std::optional<CircleCW>  calculate_transfer_circle(const CircleCCW& a, const CircleCCW& b, double r) noexcept;
///@}

/// @brief Check if circle b is inside circle a
/// @param a outside circle
/// @param b inside circle
/// @return inside (true), or not
bool inside(const Circle& a, const Circle& b) noexcept;

}    // namespace dubins


#endif    // DUBINS_CIRCLE_HPP