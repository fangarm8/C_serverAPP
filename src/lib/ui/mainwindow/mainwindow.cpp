//
// Created by pavel on 28.09.24.
//
// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"


mainwindow::mainwindow(QWidget *parent) :
    QMainWindow(parent), ui_main(new Ui::mainwindow) {
    ui_main->setupUi(this);
}

mainwindow::~mainwindow() {
    for (auto i : uis_server) {
        delete i;
    }
    for (auto i : uis_client) {
        delete i;
    }
    delete ui_main;
}

void mainwindow::on_startServer_clicked() {
    servergui * ui = new servergui();
    uis_server.push_back(ui);
    ui->show();
}

void mainwindow::on_startClient_clicked() {
    clientgui * ui = new clientgui();
    uis_client.push_back(ui);
    ui->show();
}