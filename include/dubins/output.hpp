#ifndef DUBINS_OUTPUT_HPP
#define DUBINS_OUTPUT_HPP

#include "Circle.hpp"
#include "Line.hpp"
#include "Vector.hpp"
#include "dubins/Angle.hpp"

#include <ostream>

namespace dubins
{

inline std::ostream& operator<<(std::ostream& os, const Vector2D& rhs)
{
    os << "(" << rhs.x << ", " << rhs.y << ")";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Circle& rhs)
{
    os << "{" << rhs.center << ", " << rhs.radius << "}";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Line2D& rhs)
{
    os << "{" << rhs.a << ", " << rhs.b << "}";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Angle& rhs)
{
    os << (double)rhs;
    return os;
}

}    // namespace dubins

#endif    // DUBINS_OUTPUT_HPP