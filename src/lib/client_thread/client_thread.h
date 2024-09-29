//
// Created by pavel on 29.09.24.
//

#ifndef CLIENT_THREAD_H
#define CLIENT_THREAD_H

#include <QThread>

#include "../client/Client.h"

class client_thread : public QThread {
    Q_OBJECT
public:
    client_thread(Client& client_cpy, QObject* parent = nullptr) : QThread(parent), client(client_cpy) {}
    ~client_thread() {}
    void stop() {
        running = 0;
    }
    Client& client;
signals:
    void updateReceivedData(const QString &data);
    void updateSendData(const QString &data);
protected:
    void run() override {
        client.connect();
        client.write();
        while (running) {
            client.read_do_write();
            int received_number, result_number;
            if (sscanf(client.client_info, "%d %d", &received_number, &result_number) == 2) {
                QString receivedText = "Получено: " + QString::number(received_number);
                emit updateReceivedData(receivedText);

                QString sendText = "После сложения: " + QString::number(result_number);
                emit updateSendData(sendText);
            } else {
                perror("Не удалось прочитать два числа у клиента.");
            }
            msleep(500);
        }
    }
private:
    bool running = true;
};



#endif //CLIENT_THREAD_H
