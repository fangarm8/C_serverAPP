//
// Created by pavel on 28.09.24.
//

#ifndef SERVER_H
#define SERVER_H

#define BUFFER_SIZE 256
#define INFO_SIZE 1024

#include <arpa/inet.h> //struct sockaddr_in
#include <unistd.h> //read(), write(), close()
#include <cstdio> //printf(), sprintf(), perror()
#include <cstdlib> //atoi(), exit()

class Server {
public:
    Server();
    ~Server();
    void listen(int n) const;
    void accept();
    void read();
    void write() const;
    void write(char * message) const;
    int do_math(int arg) const;
    void read_do_write();

    friend void * run_server(void * args);

    char server_info[INFO_SIZE];
    int port;
private:
    int sockfd;
    int sockfd_connect;
    char buffer[BUFFER_SIZE];
    sockaddr_in server_address;
    int variable;
    bool running;
};



#endif //SERVER_H
