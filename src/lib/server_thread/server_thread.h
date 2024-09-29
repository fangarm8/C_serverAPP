//
// Created by pavel on 29.09.24.
//

#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include <QThread>

#include "../server/Server.h"

class server_thread : public QThread {
    Q_OBJECT

public:
    server_thread(Server& server_cpy, QObject* parent = nullptr): QThread(parent), server(server_cpy) {}
    ~server_thread() {}

    void stop() {
        running = 0;
    }

    Server& server;
signals:
    void updateReceivedData(const QString &data);
    void updateSendData(const QString &data);

protected:
    void run() override {
        server.listen(1);
        server.accept();
        while (running) {
            server.read_do_write();
            int received_number, result_number;
            if (sscanf(server.server_info, "%d %d", &received_number, &result_number) == 2) {
                QString receivedText = "Получено: " + QString::number(received_number);
                emit updateReceivedData(receivedText);

                QString sendText = "После сложения: " + QString::number(result_number);
                emit updateSendData(sendText);
            } else {
                perror("Не удалось прочитать два числа у сервера.");
            }
            msleep(500);
        }
    }

private:
    bool running = 1;
};




#endif //SERVER_THREAD_H
