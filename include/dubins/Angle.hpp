#ifndef DUBINS_UTILS_HPP
#define DUBINS_UTILS_HPP


#include <cmath>
namespace dubins
{
// TODO: Make a generic angle class at some point in the future that is not so heavy handed and properly treats edge
// cases.

/// @brief Object representing an angle
class Angle
{
    public:
    /// @brief Default constructor. Angle is initialized to 0.0.
    Angle() noexcept {}

    /// @brief Double constructor. Angle is initialized to argument.
    /// @param angle angle to set
    explicit Angle(double angle) noexcept : m_value{wrap(angle)} {}

    /// @brief Double conversion
    explicit operator double() const noexcept { return m_value; }

    /// @brief Double assignment
    /// @param angle angle to assign.
    /// @return reference to this.
    Angle& operator=(double angle) noexcept
    {
        m_value = wrap(angle);
        return *this;
    }

    /// @brief Get the signed difference c = a-b, right-handed.
    /// @param a minuend
    /// @param b subtrahend
    /// @return difference
    static double signed_difference(Angle a, Angle b) noexcept
    {
        return std::fmod(((double)a - (double)b) + 3.0 * M_PI, 2.0 * M_PI) - M_PI;
    }


    /// @brief Get the positive difference c = a-b, right-handed.
    /// @param a minuend
    /// @param b subtrahend
    /// @return positive difference
    static double positive_difference(Angle a, Angle b) noexcept
    {
        const auto diff = signed_difference(a, b);
        return diff < 0.0 ? diff + 2.0 * M_PI : diff;
    }

    /// @brief Get the negative difference c = a-b, right-handed. b + c = 2pi - a
    /// @param a minuend
    /// @param b subtrahend
    /// @return negative difference
    static double negative_difference(Angle a, Angle b) noexcept
    {
        const auto diff = signed_difference(a, b);
        return diff > 0.0 ? diff - 2.0 * M_PI : diff;
    }

    private:
    /// @brief Wrap angle to [0, 2pi)
    /// @param angle argument
    /// @return result
    static double wrap(double angle) noexcept { return std::fmod(2.0*M_PI + std::fmod(angle, 2.0*M_PI), 2.0*M_PI); }

    double m_value{0.0}; ///< Store for angle
};

/// @brief Addition of two angles.
/// @param a augend
/// @param b addend
/// @return sum
inline double operator+(Angle a, Angle b)
{
    return (double)a + (double)b;
}


}    // namespace dubins


#endif    // DUBINS_UTILS_HPP