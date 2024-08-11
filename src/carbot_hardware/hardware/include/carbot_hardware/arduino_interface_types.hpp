#ifndef ARDUINO_INTERFACE__TYPES__ARDUINO_INTERFACE_TYPES_HPP_
#define ARDUINO_INTERFACE__TYPES__ARDUINO_INTERFACE_TYPES_HPP_

namespace MessageType{
  constexpr char STATUS[] = "status";

  constexpr char CONTROL[] = "control";

  constexpr char CONFIG[] = "config";

  constexpr char UNCONFIGURED[] = "unconfigured";
}

namespace TypeValue{
  constexpr char VELOCITY[] = "velocity";

  constexpr char POSITION[] = "position";

  constexpr char EFFORT[] = "effort";

  constexpr char VOLTAGE[] = "voltage";

  constexpr char LOWER_BOUND[] = "lower_bound";

  constexpr char NEUTRAL[] = "neutral";

  constexpr char UPPER_BOUND[] = "upper_bound";
}

#endif  // ARDUINO_INTERFACE__TYPES__ARDUINO_INTERFACE_TYPES_HPP_
