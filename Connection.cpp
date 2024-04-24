

#include"Connection.h"


Connection::Connection(std::string IP_address_,const uint16_t& PORT){//nessesary connection work

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		 throw std::invalid_argument("\n Socket creation error \n");
	}

    serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, IP_address_.c_str(), &serv_addr.sin_addr) <= 0) {
		throw std::invalid_argument("\nInvalid address/ Address not supported \n");
	}

    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr,sizeof(serv_addr))) < 0) {
		throw std::invalid_argument("\nConnection Failed \n");
    }

}


void Connection::Send(std::string message){

    send(client_fd, const_cast<char*>(message.c_str()), message.size(), 0);

}
	

Connection::~Connection(){
    close(client_fd);
}
