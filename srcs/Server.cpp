#include "../includes/Server.hpp"
#include "../includes/Utils.hpp"

Server* Server::singleton = NULL;
Server::Server() {}

void Server::initCommands()
{
    _commands["PASS"] = &Server::Pass;
    _commands["NICK"] = &Server::Nick;
    _commands["JOIN"] = &Server::Join;
    _commands["CAP"] = &Server::Cap;
    _commands["USER"] = &Server::User;
    _commands["MODE"] = &Server::Mode;
    _commands["WHO"] = &Server::Who;
    _commands["QUIT"] = &Server::Quit;
    _commands["PART"] = &Server::Part;
    _commands["INFO"] = &Server::Info;
}

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

void Server::setPort(size_t const& port)
{
    _port = port;
}

void Server::setPassword(std::string const& password)
{
    _password = password;
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

std::map<std::string, std::vector<std::string> > Server::getParams(std::string const& str)
{
    std::stringstream ss(str);
    std::string tmp;
    std::map<std::string, std::vector<std::string> > ret;
    ss >> tmp;
    while (1)
    {
        std::string cmd = tmp;
        std::vector<std::string> params;
        ss >> tmp;
        while (_commands.find(tmp) == _commands.end())
        {
            params.push_back(tmp);
            ss >> tmp;
            if (ss.eof()) {
                ret[cmd] = params;
                return ret;
            }
        }
        if (ss.eof()) {
            params.push_back("");
            ret[cmd] = params;
            return ret;
        }
        ret[cmd] = params;
    }
    return ret;
}

void Server::commandHandler(std::string& str, Client& cli)
{
    std::map<std::string, std::vector<std::string> > params = getParams(str);
    for (std::map<std::string, std::vector<std::string> >::iterator it = params.begin(); it != params.end(); ++it) {
        if (_commands.find(it->first) == _commands.end())
            std::cout << it->first << " command not found!" << std::endl;
        else
            (this->*_commands[it->first])(it->second, cli);
    }
}

void Server::kickClient(cliIt& it)
{
    std::cout << "Client " << it->cliFd - 3  << " disconnected!" << std::endl;
    FD_CLR(it->cliFd, &_readFds);
    FD_CLR(it->cliFd, &_writeFds);
    close(it->cliFd);
    _clients.erase(it);
}

void Server::passChecker(Client& client)
{
    if (client.passChecked == 0)
    {
        for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
            if (client.cliFd == it->cliFd)
            {
                Utils::writeMessage(client.cliFd, ERR_PASSWDMISMATCH);
                kickClient(it);
                break;
            }
        }
    }
}

int Server::isNickExist(std::string const& nick)
{
    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->nick == nick)
            return 1;
    }
    return 0;
}

void Server::readEvent()
{
    int readed;

    for (cliIt it = _clients.begin(); it != _clients.end(); ++it) {
        if (FD_ISSET(it->cliFd, &_readFdsSup))
        {
            readed = recv(it->cliFd, buffer, 1024, 0);
            if (readed <= 0) {
                kickClient(it);
                break;
            }
            else
            {
                buffer[readed] = 0;
                std::string tmp = buffer;
                if (tmp == "\n")
                    break;
                std::cout << buffer;
                commandHandler(tmp, *it);
                break;
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
        
        // write event
        
    }
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
    initCommands();
    createSocket();
    bindSocket(port);
    printStatus();
    run();
}
