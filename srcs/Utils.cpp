#include "../includes/Utils.hpp"
#include <unistd.h>

void Utils::writeMessage(int socket, std::string message)
{
    if (write(socket, message.c_str(), sizeof(message) + 2) < 0)
        std::cout << "Welcome message cannot send!" << std::endl;
}


std::string Utils::getCmd(std::string const& str)
{
    std::stringstream ss(str);  
    std::string ret;
    ss >> ret;
    return ret;
}

std::vector<std::string> Utils::getParam(std::string const& str)
{
    std::stringstream ss(str);
    std::vector<std::string> ret;
    std::string tmp;
    ss >> tmp;
    while (ss >> tmp)
        ret.push_back(tmp);
    return ret;
}
