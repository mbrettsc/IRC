#include "../includes/Utils.hpp"
#include <unistd.h>

void Utils::writeMessage(int socket, std::string const& message)
{
    if ((write(socket, message.c_str(), message.length())) < 0)
        std::cout << "Message cannot send!" << std::endl;
}
