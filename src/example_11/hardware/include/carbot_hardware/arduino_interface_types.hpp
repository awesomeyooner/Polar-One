#ifndef ARDUINO_INTERFACE__TYPES__ARDUINO_INTERFACE_TYPES_HPP_
#define ARDUINO_INTERFACE__TYPES__ARDUINO_INTERFACE_TYPES_HPP_

namespace ArduinoValue{

//message_type macros
constexpr char STATUS[] = "status";

constexpr char CONTROL[] = "control";

constexpr char CONFIG[] = "config";

//type_value macros
constexpr char VELOCITY[] = "velocity";

constexpr char POSITION[] = "position";

constexpr char PERCENT[] = "percent";

constexpr char VOLTAGE[] = "voltage";
}  // namespace ArduinoValue

#endif  // ARDUINO_INTERFACE__TYPES__ARDUINO_INTERFACE_TYPES_HPP_
