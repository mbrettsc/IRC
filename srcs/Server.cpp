#include "../includes/Server.hpp"
#include "../includes/Utils.hpp"

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
    if ((_serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        throw std::runtime_error("Socket");

    const int enable = 1;
    if (setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        throw std::runtime_error("Setsockopt");
}

void Server::bindSocket(size_t const & port)
{
    struct sockaddr_in server_addr;


    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (bind(_serverFd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        throw std::runtime_error("Bind");

    if (listen(_serverFd, 128) < 0)
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
    if (atoi(port.c_str()) > 65535)
        return 0;
    return 1;
}

void Server::acceptRequest()
{
    Client tmp;
    sockaddr_in cliAddr;
    socklen_t cliSize = sizeof(cliAddr);

    tmp.cliFd = accept(_serverFd, (sockaddr *)&cliAddr, &cliSize);
    if (tmp.cliFd <= 0)
        throw std::runtime_error("Accept failed");
    tmp.port = ntohs(cliAddr.sin_port);
    inet_ntop(AF_INET, &(cliAddr.sin_addr), tmp.ipAddr, INET_ADDRSTRLEN);
    FD_SET(tmp.cliFd, &_readFds);
    std::cout << "New client connected!" << std::endl;
    Utils::writeMessage(tmp.cliFd, "Welcome to our irc server\n");
    _clients.push_back(tmp);
}

void Server::readEvent()
{
    int readed;
    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
        if (FD_ISSET(it->cliFd, &_readFdsSup))
        {
            readed = read(it->cliFd, buffer, 1024);
            if (readed <= 0)
            {
                FD_CLR(it->cliFd, &_readFdsSup);
                FD_CLR(it->cliFd, &_writeFdsSup);
                close(it->cliFd);
                _clients.erase(it);
                std::cout << it->nick <<  "client disconnected!" << std::endl;
            }
            else
            {
                buffer[readed] = 0;
                std::string tmp = buffer;
                std::cout << buffer;
            }
        }
    }
}

void Server::initFds()
{
    FD_ZERO(&_readFds);
    FD_ZERO(&_writeFds);
    FD_ZERO(&_readFdsSup);
    FD_ZERO(&_writeFdsSup);
    FD_SET(_serverFd, &_readFds);
}

void Server::run()
{
    int state = 0;

    initFds();
    while (1)
    {
        while (state == 0)
        {
            _readFdsSup = _readFds;
            _writeFdsSup = _writeFds;
            state = select(_clients.size() + 4, &_readFdsSup, &_writeFdsSup, NULL, 0);
        }
        // new connection
        if (FD_ISSET(_serverFd, &_readFdsSup)) {
            acceptRequest();
            state = 0;
            continue;
        }
        
        // read event
        if (state) {
            readEvent();
            state = 0;
            continue;
        }        
    }
}

void Server::setPort(size_t const& port)
{
    _port = port;
}

void Server::printStatus()
{
    char name[255];

    gethostname(name, sizeof(name));
    std::cout << "Port: " << _port << std::endl;
    std::cout << "Password: " << _password << std::endl;
    std::cout << "Server running on: " << name << std::endl;
}

void Server::manageServer(size_t const& port, std::string const& password)
{
    setPort(port);
    setPassword(password);
    createSocket();
    bindSocket(port);
    printStatus();
    run();
}
