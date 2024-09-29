//
// Created by pavel on 28.09.24.
//

#ifndef CLIENT_H
#define CLIENT_H

#define BUFFER_SIZE 256
#define INFO_SIZE 1024

#include <arpa/inet.h> //struct sockaddr_in

class Client
{
public:
    Client();
    ~Client();
    void connect();
    void set_port(int port_cpy);
    void read();
    void write();
    void read_do_write();
    void * run();

    char client_info[1024];
    int port;
private:
    int sockfd;
    sockaddr_in server_address;
    char buffer[256];
    int variable;
    bool running;
};


#endif //CLIENT_H
