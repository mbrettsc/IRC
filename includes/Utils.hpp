#pragma once

#include <iostream>
#include <sstream>
#include "../includes/Server.hpp"

#define ERR_NICKNAMEINUSE(source)				    ": 433 " + source + " " + source  + " :Nickname is already in use" + "\r\n"         //NICK
#define ERR_NICKNAMEEMPTY(source)				    ": 433 " + source + " " + source  + " :Nickname cannot empty" + "\r\n"              //NICK

#define ERR_NEEDMOREPARAMS "Need more or less params\r\n"

#define ERR_ALREADYREGISTRED "Already registered\r\n"

#define ERR_BADCHANNELKEY "Bad key"

class Utils
{
public:
    static void writeMessage(int, std::string const&);
    static std::string getCmd(std::string const&);
    static std::vector<std::string> getParam(std::string const&);
};
