
#ifndef DUBINS_VECTOR_HPP
#define DUBINS_VECTOR_HPP

#include <cmath>

namespace dubins
{
/// @brief Object to hold 2D vector data
struct Vector2D
{
    double x{0.0};    ///< x location of vector
    double y{0.0};    ///< y location of vector
};

// Vector operations

/// @brief Find the L2 norm of a vector
/// @param lhs vector
/// @return L2 norm
inline double norm(const Vector2D& lhs)
{
    return std::sqrt(lhs.x * lhs.x + lhs.y * lhs.y);
}

/// @brief Find the L2 norm squared of a vector
/// @param lhs vector
/// @return L2 norm squared
inline constexpr double normsq(const Vector2D& lhs)
{
    return std::abs(lhs.x * lhs.x + lhs.y * lhs.y);
}

/// @brief Find the inner product of two vectors a*b
/// @param lhs vector a
/// @param rhs vector b
/// @return inner product
inline constexpr double inner(const Vector2D& lhs, const Vector2D& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

/// @brief Find the outer product of two vectors axb
/// @param lhs vector a
/// @param rhs vector b
/// @return outer product (z component for 2D vectors)
inline constexpr double outer(const Vector2D& lhs, const Vector2D& rhs)
{
    return lhs.x * rhs.y - rhs.x * lhs.y;
}

// Algebraic operators

/// @brief Find the sum of two vectors a*b
/// @param lhs vector a
/// @param rhs vector b
/// @return resultant vector
inline Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

/// @brief Vector negation
/// @param rhs vector
/// @return resultant vector
inline Vector2D operator-(const Vector2D& rhs)
{
    return {-rhs.x, -rhs.y};
}

/// @brief Vector subtraction
/// @param lhs vector a
/// @param rhs vector b
/// @return resultant vector
inline Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs)
{
    return lhs + (-rhs);
}

// Boolean operators
/// @brief Boolean equals comparison
/// @param lhs vector a
/// @param rhs vector b
/// @return equal (true), or not equal
inline bool operator==(const Vector2D& lhs, const Vector2D& rhs)
{
    return lhs.x == rhs.x & lhs.y == rhs.y;
}

/// @brief Boolean not equals comparison
/// @param lhs vector a
/// @param rhs vector b
/// @return not equal (true), or equal
inline bool operator!=(const Vector2D& lhs, const Vector2D& rhs)
{
    return !(lhs == rhs);
}

}    // namespace dubins

#endif    // DUBINS_VECTOR_HPP