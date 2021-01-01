#ifndef DUBINS_LINE_HPP
#define DUBINS_LINE_HPP

#include "Vector.hpp"

namespace dubins
{
/// @brief Object representing a line
struct Line2D
{
    using Point = Vector2D;    ///< Alias for a point type
    Point a;                   ///< Start point of line
    Point b;                   ///< Start point of line
};

/// @brief Length squared of the line segment.
/// @param line Line
/// @return length squared
inline constexpr double length_sq(const Line2D& line) noexcept
{
    return norm_sq(line.b - line.a);
};

/// @brief Length of the line segment
/// @param line Line
/// @return length
inline double length(const Line2D& line) noexcept
{
    return std::sqrt(length_sq(line));
}

}    // namespace dubins

#endif    // DUBINS_LINE_HPP