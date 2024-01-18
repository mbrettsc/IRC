#include "../includes/Utils.hpp"
#include <unistd.h>

void Utils::writeMessage(int socket, std::string const& message)
{
    if ((write(socket, message.c_str(), message.length())) < 0)
        std::cout << "Message cannot send!" << std::endl;
}

void Utils::writeAllMessage(std::vector<int> const& fds, std::string const& message)
{
    for (std::vector<int>::const_iterator it = fds.begin(); it != fds.end(); ++it) {
        writeMessage(*it, message);
    }
}
