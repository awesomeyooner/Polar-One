#ifndef ARDUINO_INTERFACE__TYPES__ARDUINO_INTERFACE_TYPES_HPP_
#define ARDUINO_INTERFACE__TYPES__ARDUINO_INTERFACE_TYPES_HPP_

namespace ArduinoUtility{

  struct ArduinoMessage{
    std::string device = ""; //(id) left, right, voltage_sensor
    std::string message_type = ""; //status, control, config
    std::string type_value = ""; //velocity, position, percent, inverted
    double value = 0; //whatever value you want to send
  };

}

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

  constexpr char RAW[] = "raw";

  constexpr char LOWER_BOUND[] = "lower_bound";

  constexpr char NEUTRAL[] = "neutral";

  constexpr char UPPER_BOUND[] = "upper_bound";
}

#endif  // ARDUINO_INTERFACE__TYPES__ARDUINO_INTERFACE_TYPES_HPP_
