//
// Created by pavel on 28.09.24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_servergui.h" resolved


#include "servergui.h"
#include "ui_servergui.h"

servergui::servergui(QWidget *parent) :
    QWidget(parent), ui(new Ui::servergui) {
    ui->setupUi(this);
    server = new Server();
    ui->ServerPort->setText(QStringLiteral("Сервер работает на порте: %1").arg(server->port));
    sthread = new server_thread(*server);
    connect(sthread, &server_thread::updateReceivedData, ui->ReceivedData, &QLabel::setText);
    connect(sthread, &server_thread::updateSendData, ui->SendData, &QLabel::setText);
    sthread->start();
}

servergui::~servergui() {
    delete sthread;
    delete server;
    delete ui;
}
