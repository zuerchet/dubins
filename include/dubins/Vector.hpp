
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

/// @brief Find the inner product of two vectors a*b
/// @param lhs vector a
/// @param rhs vector b
/// @return inner product
inline constexpr double inner(const Vector2D& lhs, const Vector2D& rhs) noexcept
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

/// @brief Find the outer product of two vectors axb
/// @param lhs vector a
/// @param rhs vector b
/// @return outer product (z component for 2D vectors)
inline constexpr double outer(const Vector2D& lhs, const Vector2D& rhs) noexcept
{
    return lhs.x * rhs.y - rhs.x * lhs.y;
}

// Algebraic operators

/// @brief Find the sum of two vectors a*b
/// @param lhs vector a
/// @param rhs vector b
/// @return resultant vector
inline constexpr Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs) noexcept
{
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

/// @brief Vector negation
/// @param rhs vector
/// @return resultant vector
inline constexpr Vector2D operator-(const Vector2D& rhs) noexcept
{
    return {-rhs.x, -rhs.y};
}

/// @brief Vector subtraction
/// @param lhs vector a
/// @param rhs vector b
/// @return resultant vector
inline constexpr Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs) noexcept
{
    return lhs + (-rhs);
}

/// @brief Vector scalar multiplication a*B
/// @param lhs scalar a
/// @param rhs vector B
/// @return resultant vector
inline constexpr Vector2D operator*(const double lhs, const Vector2D& rhs) noexcept
{
    return {lhs*rhs.x, lhs*rhs.y};
}

/// @brief Vector scalar multiplication A*b
/// @param lhs vector A
/// @param rhs scalar b
/// @return resultant vector
inline constexpr Vector2D operator*(const Vector2D& lhs, const double rhs) noexcept
{
    return rhs*lhs;
}

/// @brief Vector scalar division B/a
/// @param lhs vector A
/// @param rhs scalar b
/// @return resultant vector
inline constexpr Vector2D operator/(const Vector2D& lhs, const double rhs) noexcept
{
    return (1.0/rhs)*lhs;
}

// Vector operations

/// @brief Find the L2 norm squared of a vector
/// @param lhs vector
/// @return L2 norm squared
inline constexpr double norm_sq(const Vector2D& lhs) noexcept
{
    return std::abs(lhs.x * lhs.x + lhs.y * lhs.y);
}

/// @brief Find the L2 norm of a vector
/// @param lhs vector
/// @return L2 norm
inline double norm(const Vector2D& lhs) noexcept
{
    return std::sqrt(norm_sq(lhs));
}

/// @brief Get normalized vector
/// @param a vector A
/// @return vector normalized to a unit length
inline Vector2D normalize(const Vector2D& a) noexcept
{
    return a/norm(a);
}

/// @brief Get perpendicular vector
/// @param a vector A
/// @return vector perpendicular to A
inline constexpr Vector2D perpendicular(const Vector2D& a) noexcept
{
    return {-a.y, a.x};
}

}    // namespace dubins

#endif    // DUBINS_VECTOR_HPP