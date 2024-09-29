//
// Created by pavel on 28.09.24.
//

#include "Server.h"

#include <cstring> //memset()


Server::Server() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Ошибка при открытии сокета");
        exit(1);
    }

    memset((char*)&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    for (port = 1024; port < 65535; port++) {
        server_address.sin_port = htons(port);
        if (bind(sockfd, reinterpret_cast<sockaddr *>(&server_address), sizeof(server_address)) == 0) {
            break;
        }
    }
    if (port >= 65535) {
        perror("Ошибка привязки");
        ::close(sockfd);
        exit(1);
    }

    printf("Сервер слушает порт: %d\n", port);

    sockfd_connect = 0;
    memset(buffer, 0, BUFFER_SIZE);
    memset(server_info, 0, INFO_SIZE);
    variable = 5;
    running = true;
}

Server::~Server() {
    ::close(sockfd);
    ::close(sockfd_connect);
    memset(buffer, 0, 256);
    memset((char*)&server_address, 0, sizeof(server_address));
}

void Server::listen(const int n) const {
    ::listen(sockfd, n);
}

void Server::accept() {
    sockfd_connect = ::accept(sockfd, 0, 0);
    if (sockfd_connect < 0) {
        perror("Ошибка при принятии соединения");
    }
}

void Server::read() {
    memset(buffer, 0, BUFFER_SIZE);
    ssize_t n = ::read(sockfd_connect, buffer, BUFFER_SIZE);
    if (n < 0) {
        perror("Ошибка чтения из сокета");
    }
    int tmp = atoi(buffer);
    sprintf(server_info, "%d", tmp);
}

void Server::write() const {
    ::write(sockfd_connect, buffer, BUFFER_SIZE - 1);
}

void Server::write(char* buff) const {
    ::write(sockfd_connect, buff, sizeof(buff));
}

int Server::do_math(int arg) const {
    return variable + arg;
}

void Server::read_do_write() {
    memset(buffer, 0, 256);
    int n = ::read(sockfd_connect, buffer, 255);
    if (n < 0) {
        perror("Ошибка чтения из сокета");
    }
    int received_number = atoi(buffer);
    int result_number = received_number + variable;
    sprintf(buffer, "%d", result_number);
    ::write(sockfd_connect, buffer, 255);

    sprintf(server_info, "%d %d", received_number, result_number);
}

void * run_server(void * args) {
    Server * server = static_cast<Server *>(args);
    server->listen(1);
    server->accept();
    while (server->running) {
        server->read();
        const int received_number = atoi(server->buffer);
        const int result_number = server->do_math(received_number);
        sprintf(server->server_info, "%d %d", received_number, result_number);
        server->write();
        printf("Получено: %d\t Отправлено: %d\n", received_number, result_number);
        sleep(2);
    }
}