#ifndef CUSTOM_VALIDATORS_HPP
#define CUSTOM_VALIDATORS_HPP

#include <fmt/core.h>

#include <string>

#include <rclcpp/rclcpp.hpp>
#include <rsl/parameter_validators.hpp>
#include <tl_expected/expected.hpp>

namespace ackermann_drive_controller
{

/**
 * @brief gt_eq, but check only if the value is not NaN
 */
template <typename T>
tl::expected<void, std::string> gt_eq_or_nan(rclcpp::Parameter const & parameter, T expected_value)
{
  auto param_value = parameter.as_double();
  if (!std::isnan(param_value))
  {
    // check only if the value is not NaN
    return rsl::gt_eq<T>(parameter, expected_value);
  }
  return {};
}

/**
 * @brief lt_eq, but check only if the value is not NaN
 */
template <typename T>
tl::expected<void, std::string> lt_eq_or_nan(rclcpp::Parameter const & parameter, T expected_value)
{
  auto param_value = parameter.as_double();
  if (!std::isnan(param_value))
  {
    // check only if the value is not NaN
    return rsl::lt_eq<T>(parameter, expected_value);
  }
  return {};
}

}  // namespace ackermann_drive_controller

#endif // CUSTOM_VALIDATORS_HPP