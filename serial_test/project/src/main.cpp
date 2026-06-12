#include <string>
#include <iostream>
#include <unistd.h>
#include <cstdint>
#include <unistd.h>
#include <thread>
#include <ctime>
#include <fstream>
#include <mutex>

#include "CommiFaceLib/protocols/serial.hpp"

#include "plib/util/util.hpp"

#include <libserial/SerialPort.h>


using namespace status_utils;


const std::string DEVICE_PRODUCT = "STM32 Virtual ComPort";


int main(int argc, char* argv[])
{
    System::initialize();

    SerialInterface serial;

    if(serial.init_field("product", DEVICE_PRODUCT) != StatusCode::OK)
    {
        Logger::error("Exiting...");
        return 1;
    }


    while(System::is_alive())
    {
        auto input = util::get_user_input_double("[ INT ] >> ");

        if(!input.is_OK())
        {
            System::shutdown();
            break;
        }

        serial.write_double(101, input.value);

        auto status = serial.request_double(99);

        if(!status.is_OK())
        {
            Logger::debug("Failed to receive data.");
            continue;
        }

        Logger::info(status.value);
    }

    Logger::info("Closing Serial Port...");
    serial.close();

    Logger::info("Exiting...");

    return 0;
}