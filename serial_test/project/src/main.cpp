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

        std::vector<uint8_t> data = ByteConverter::double_to_bytes(input.value);

        serial.write_to_register(100, data);

        // auto status = serial.receive_bytes((int)input.value.length(), 1000);

        // if(!status.is_OK())
        // {
        //     Logger::debug("what");
        //     continue;
        // }

        // std::string read_data = ByteConverter::bytes_to_string(status.value);

        // std::cout << read_data << std::endl;
    }

    Logger::info("Closing Serial Port...");
    serial.close();

    Logger::info("Exiting...");

    return 0;
}