#include "../includes/Utils.hpp"
#include <unistd.h>

void Utils::writeMessage(int socket, std::string message)
{
    if (write(socket, message.c_str(), sizeof(message) + 2) < 0)
        std::cout << "Welcome message cannot send!" << std::endl;
}
