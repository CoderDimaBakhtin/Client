


#ifndef CONNECTION_H
#define CONNECTION_H


#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include<string>
#include <stdexcept> 





class Connection{
private:
    int status, valread, client_fd;
	struct sockaddr_in serv_addr;
    char buffer[1024] = { 0 };
public:

    Connection(std::string IP_address_,const uint16_t& PORT);

    void Send(std::string message);

	~Connection();
};


#endif