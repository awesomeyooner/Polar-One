# Polar-One
Polar One is an Autonomous RC Car running ROS 2 as the main framework for all subsystems. This project was initially for the Boeing High school internship but will be continued afterwards.

## Hardware
The base chassis of this car is the [Exceed RC 1/16 Legion Desert Monster Truck](https://www.nitrorcx.com/51c854-16-desertmonster-ddblue-24g.html), using a standard 6KG servo for steering and a brushed 380 motor controlled by a HobbyWing 1625 ESC. 

Components:
- N97 GMTek Nucbox for all highlevel computing
- PCA 9865 PWM driver
- ESP32 Devkit 1 for low level hardware control
- Mango Router for Access Point
- Pololu 12V Step Up converter for powering the NucBox
- 1 7.2V NiMH battery for powering the ESC
- 1 9.6 NiMH nunchuck battery for powering the NucBox

## Software
The NucBox runs Ubuntu 22.04 headless and ROS 2 Humble Hawksbill. Custom made Hardware Interface with the ESP32 allows the servo and ESC to be controlled through ROS topics. The ESP32 and the NucBox communicate through Serial and Json packets for sending different packets of information. 

For the Autonomous driving part, the plan is to use an AR0144 camera and OpenCV to detect lanes and feed the amount of turn to a PID controller to keep it steady. 
