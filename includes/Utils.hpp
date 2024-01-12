#pragma once

#include <iostream>
#include <sstream>

class Utils
{
public:
    static void writeMessage(int socket, std::string message);
    static std::string getCmd(std::string const&);
    static std::vector<std::string> getParam(std::string const&);
};
