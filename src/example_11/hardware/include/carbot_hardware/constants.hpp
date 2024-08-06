#include <string>


namespace MotorConstants{
  const std::string DEVICE = "virtual_rear_wheel_joint";

  const int MAX_FORWARD = 600;
  const int NEUTRAL = 330;
  const int MAX_REVERSE = 60;

  const int CHANNEL = 0;
}

namespace ServoConstants{
  const std::string DEVICE = "virtual_front_wheel_joint";

  const int MAX_LEFT = 520;
  const int NEUTRAL = 400;
  const int MAX_RIGHT = 280;

  const int CHANNEL = 1;
}

namespace VoltageSensorConstants{
  const std::string DEVICE = "voltage_sensor";

  const int CHANNEL = 1;
}
 