#include "../includes/Server.hpp"

Server* Server::serverPtr = NULL;

Server::Server()
{
    fd = socket(AF_INET, SOCK_STREAM, 0);
}

Server::~Server() {}

Server* Server::getInstance()
{
    if (serverPtr == NULL)
        serverPtr = new Server;
    return serverPtr;
}
