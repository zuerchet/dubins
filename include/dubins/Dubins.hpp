#ifndef DUBINS_DUBINS_HPP
#define DUBINS_DUBINS_HPP

#include "dubins/Vector.hpp"

#include <cstdint>
#include <memory>
#include <vector>

namespace dubins
{
/// @brief Object representing state on path
struct State
{
    Vector2D position;    ///< Position
    double   heading;     ///< Heading
};

/// @brief Object for calculating the dubins shortest path
class Dubins
{
    public:
    /// @brief Options for calculating dubins shortest path
    struct Options
    {
        double       turning_radius{1.0};           ///< Turing radius of Dubins car
        double       max_segment_length{0.1};       ///< Max length between points on returned path.
        std::int32_t min_number_of_segments{30};    ///< Minimum number of segments on returned path.
    };


    /// @brief Create shortest path between start and end state
    /// @param start State of the path start
    /// @param end State at the path end
    /// @param options Options for generating path
    /// @return Object representing a dubins shortest path
    Dubins(const State& start, const State& end, const Options& options) noexcept;

    /// @brief Destructor
    ~Dubins();

    /// @brief Get the length of the path
    /// @return length of the path
    double length() noexcept;

    /// @brief Get the path seperated into segments
    /// @param options Options for generating path
    std::vector<State> segmented_path(const Options& options) noexcept;


    /// @brief Get the rsr generated path
    /// @param options Options for generating path
    std::vector<State> segmented_rsr(const Options& options) noexcept;

    /// @brief Get the lsl generated path
    /// @param options Options for generating path
    std::vector<State> segmented_lsl(const Options& options) noexcept;

    /// @brief Get the rsl generated path
    /// @param options Options for generating path
    std::vector<State> segmented_rsl(const Options& options) noexcept;

    /// @brief Get the lsr generated path
    /// @param options Options for generating path
    std::vector<State> segmented_lsr(const Options& options) noexcept;

    /// @brief Get the lrl generated path
    /// @param options Options for generating path
    std::vector<State> segmented_lrl(const Options& options) noexcept;

    /// @brief Get the rlr generated path
    /// @param options Options for generating path
    std::vector<State> segmented_rlr(const Options& options) noexcept;

    private:
    /// @brief Internal implementation of dubins path class
    class Path;

    std::unique_ptr<Path> pimpl;    ///< Pointer to interal path data
};

}    // namespace dubins


#endif    // DUBINS_DUBINS_HPP