#include "socket.hpp"

int main()
{
    char buff[1024] = { 0 };
 
    Socket serverSock;
    serverSock.bind_it();
    int client_fd;
    while (1)
    {
        if ((client_fd = accept(serverSock.getFd(), (struct sockaddr *) &serverSock.getAddr(), &serverSock.getLen())))
        {
            if (!fork())
            {
                recv(client_fd, buff, 1024, 0);
                std::cout << buff << std::endl;
                exit(0);
            }
        }
    }
    return 0;
}