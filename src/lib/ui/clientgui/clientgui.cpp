//
// Created by pavel on 28.09.24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_clientgui.h" resolved

#include "clientgui.h"
#include "ui_clientgui.h"


clientgui::clientgui(QWidget *parent) :
    QWidget(parent), ui(new Ui::clientgui) {
    ui->setupUi(this);
    client = new Client();
    cthread = new client_thread(*client);
    connect(cthread, &client_thread::updateReceivedData, ui->ReceivedLabel, &QLabel::setText);
    connect(cthread, &client_thread::updateSendData, ui->SendLabel, &QLabel::setText);
}

void clientgui::on_ConnectButton_clicked() {
    client->set_port(static_cast<int>(ui->PortEdit->text().toInt()));
    cthread->start();
}

clientgui::~clientgui() {
    delete cthread;
    delete client;
    delete ui;
}
