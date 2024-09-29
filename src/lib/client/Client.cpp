//
// Created by pavel on 28.09.24.
//

#include <unistd.h> //read(), write(), close()
#include <cstdio> //printf(), sprintf(), perror()
#include <cstdlib> //atoi(), exit()
#include <cstring> //memset()

#include "Client.h"

Client::Client() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Ошибка при открытии сокета");
        exit(1);
    }
    port = 0;
    variable = 5;
    running = true;
    memset((char*)&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(port);
    memset(buffer, 0, BUFFER_SIZE);
    memset(client_info, 0, INFO_SIZE);
}

Client::~Client() {
    ::close(sockfd);
    memset(buffer, 0, BUFFER_SIZE);
    memset((char*)&server_address, 0, sizeof(server_address));
}

void Client::connect() {
    server_address.sin_port = htons(port);
    if (::connect(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Ошибка соединения для отправки");
        close(sockfd);
        exit(1);
    }
}

void Client::set_port(int port_cpy) {
    port = port_cpy;
}

void Client::read() {
    memset(buffer, 0, BUFFER_SIZE);
    int n = ::read(sockfd, buffer, BUFFER_SIZE - 1);
    if (n <= 0) {
        perror("Ошибка чтения из сокета");
        sleep(1);
    }
}

void Client::write() {
    sprintf(buffer, "%d", variable);
    ::write(sockfd, buffer, BUFFER_SIZE - 1);
}
void Client::read_do_write() {
    memset(buffer, 0, BUFFER_SIZE);
    int n = ::read(sockfd, buffer, BUFFER_SIZE - 1);
    if (n < 0) {
        perror("Ошибка чтения из сокета");
    }
    int received_number = atoi(buffer);
    int result_number = received_number + variable;
    sprintf(buffer, "%d", result_number);
    ::write(sockfd, buffer, BUFFER_SIZE - 1);

    sprintf(client_info, "%d %d", received_number, result_number);
}

void *Client::run() {
    connect();
    write();
    while (running) {
        read();
        int received_number = atoi(buffer);
        int result_number = received_number + variable;
        sprintf(buffer, "%d", result_number);
        write();
        sprintf(client_info, "%d %d", received_number, result_number);
        printf("Получено: %d\t Отправлено: %d\n", received_number, result_number);
        sleep(2);
    }
    return nullptr;
}
