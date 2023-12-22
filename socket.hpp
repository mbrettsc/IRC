#pragma once

#define PORT 9192
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>

void exit_err(std::string err) {
    std::cout << "Error: " << err << std::endl;
    exit(1);
}

class Socket
{
public:
    Socket() {
        socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_fd <= 0)
            exit_err("socket");
        sock_addr.sin_port = PORT;
        sock_addr.sin_addr.s_addr = INADDR_ANY;
        sock_addr.sin_family = AF_INET;
        len = sizeof(sock_addr);
    }
    int bind_it() {
        if (bind(socket_fd, (struct sockaddr *) &sock_addr, len))
            exit_err("bind");
        listen(socket_fd, 128);
        return 1;
    }
    ~Socket() {
        close(socket_fd);
    }
    int getFd() const {
        return socket_fd;
    }
    struct sockaddr_in & getAddr()  {
        return sock_addr;
    }
    socklen_t & getLen() {
        return len;
    }
private:
    int socket_fd;
    struct sockaddr_in sock_addr;
    socklen_t len;
};
