#include "../../includes/Bot.hpp"

Bot* Bot::singleton = NULL;

Bot* Bot::getInstance()
{
    if (singleton == NULL)
        singleton = new Bot;
    return singleton;
}

Bot::~Bot()
{
    if (singleton != NULL)
        delete singleton;
    singleton = NULL;
}

void Bot::setPasword(std::string const& password)
{
    _password = password;
}

void Bot::setPort(int port)
{
    _port = port;
}

void Bot::createSocket()
{
    if ((_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw std::runtime_error("socket() failed");
    
    const int enable = 1;
    if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        throw std::runtime_error("setsockopt() failed");
}

void Bot::run(int port, std::string const& password)
{
    setPasword(password);
    setPort(port);
    createSocket();
}
