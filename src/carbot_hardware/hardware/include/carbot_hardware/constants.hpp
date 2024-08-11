#include <string>


namespace MotorConstants{
  const std::string DEVICE = "virtual_rear_wheel_joint";

  const int MAX_FORWARD = 500;
  const int NEUTRAL = 360;
  const int MAX_REVERSE = 280;

  const int CHANNEL = 0;
}

namespace ServoConstants{
  const std::string DEVICE = "virtual_front_wheel_joint";

  const int MAX_LEFT = 520;
  const int NEUTRAL = 365;
  const int MAX_RIGHT = 260;

  const int CHANNEL = 1;
}

namespace VoltageSensorConstants{
  const std::string DEVICE = "voltage_sensor";

  const int CHANNEL = 1;
}
 