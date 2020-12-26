#ifndef DUBINS_CIRCLE_HPP
#define DUBINS_CIRCLE_HPP

#include "dubins/Vector.hpp"

namespace dubins
{
/// @brief Object representing a circle
struct Circle
{
    public:
    Vector2D center;         ///< Center of the circle
    double   radius{0.0};    ///< Radius of the circle
};

// Boolean operators
/// @brief Boolean equals comparison
/// @param lhs circle a
/// @param rhs circle b
/// @return equal (true), or not
inline bool operator==(const Circle& lhs, const Circle& rhs)
{
    return lhs.center == rhs.center && lhs.radius == rhs.radius;
}

/// @brief Boolean not equals comparison
/// @param lhs circle a
/// @param rhs circle b
/// @return not equal (true), or equal
inline bool operator!=(const Circle& lhs, const Circle& rhs)
{
    return !(lhs == rhs);
}
}    // namespace dubins


#endif    // DUBINS_CIRCLE_HPP