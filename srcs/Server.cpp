#include "../includes/Server.hpp"

Server* Server::singleton = NULL;

Server::Server() {}

Server::~Server()
{
    if (singleton != NULL)
        delete singleton;
    singleton = NULL;
}

Server* Server::getInstance()
{
    if (singleton == NULL)
        singleton = new Server;
    return singleton;
}

void Server::createSocket()
{
    if ((_sockFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        throw std::runtime_error("Socket");

    const int enable = 1;
    if (setsockopt(_sockFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        throw std::runtime_error("Setsockopt");
}

void Server::bindSocket(size_t const & port)
{
    struct sockaddr_in server_addr;

    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (bind(_sockFd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        throw std::runtime_error("Bind");

    if (listen(_sockFd, 128) < 0)
        throw std::runtime_error("Listen");
}

void Server::setPassword(std::string const& password)
{
     _password = password;
}

int Server::portIsValid(std::string const& port)
{
    for (size_t i = 0; i < port.size(); ++i) {
        if (!isdigit(port[i]))
            return 0;
    }
    return 1;
}

void Server::manageServer(size_t const& port, std::string const& password)
{
    setPassword(password);
    createSocket();
    bindSocket(port);
}
