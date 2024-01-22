#pragma once

// Singleton design pattern

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <vector>
#include <map>
#include <fcntl.h>
#include "Client.hpp"
#include "Channel.hpp"
#include "Utils.hpp"

class Server;
typedef void (Server::*Commands)(std::vector<std::string>& , Client&);
typedef std::vector<Client>::iterator cliIt;
typedef std::vector<Channel>::iterator chanIt;

class Server
{
private:
    // variables
    int _serverFd;
    size_t _port;
    std::string _password;
    std::vector<Client> _clients;
    char buffer[1024];
    std::map<std::string, Commands> _commands;
    std::vector<Channel> _channels;
    // fd_set's
    fd_set _readFds;
    fd_set _writeFds;
    fd_set _readFdsSup;
    fd_set _writeFdsSup;
    // methods
    Server();
    std::map<std::string, std::vector<std::string> > getParams(std::string const& str);
    static Server* singleton;
    void showRightGui(Client &cli, Channel &cha);
    int isNickExist(std::string const&);
    int getOpFd(std::string const& opName);
    int clientIsInThere(Client&, std::string const&);
    int isChannelExist(std::string const&);
    void toChannel(std::vector<std::string>&, Client&);
    void toClient(std::vector<std::string>&, Client&);
    void createSocket();
    void bindSocket(size_t const&);
    void setPort(size_t const&);
    void setPassword(std::string const&);
    Channel& getChannel(std::string const&);
    void printStatus();
    void acceptRequest();
    void readEvent(int*);
    void writeEvent();
    void initFds();
    void initCommands();
    void run();
    void passChecker(Client&);
    void kickClient(cliIt&);
    void commandHandler(std::string&, Client&);
    void modesOp(chanIt&, std::vector<std::string>& param, int* flag);
    void modesLimit(chanIt&, std::vector<std::string>& param, int* flag);
    void modesKey(chanIt&, std::vector<std::string>& param, int* flag);
    void getAfterColon(std::vector<std::string>& param);
    // commands
    void Pass(std::vector<std::string>&, Client&);
    void Nick(std::vector<std::string>&, Client&);
    void Join(std::vector<std::string>&, Client&);
    void Cap(std::vector<std::string>&, Client&);
    void User(std::vector<std::string>&, Client&);
    void Mode(std::vector<std::string>&, Client&);
    void Who(std::vector<std::string>&, Client&);
    void Whois(std::vector<std::string>&, Client&);
    void Quit(std::vector<std::string>&, Client&);
    void Part(std::vector<std::string>&, Client&);
    void Info(std::vector<std::string>&, Client&);
    void Privmsg(std::vector<std::string>&, Client&);
    void Kick(std::vector<std::string>&, Client&);
    void Topic(std::vector<std::string>&, Client&);
    void Notice(std::vector<std::string>&, Client&);
    void List(std::vector<std::string>&, Client&);
    void Invite(std::vector<std::string>&, Client&);
public:
    ~Server();
    static int portIsValid(std::string const&);
    void manageServer(size_t const &, std::string const &);
    static Server* getInstance();
};
