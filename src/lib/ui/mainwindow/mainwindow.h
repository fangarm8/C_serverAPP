//
// Created by pavel on 28.09.24.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../servergui/servergui.h"
#include "../clientgui/clientgui.h"


QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QMainWindow {
Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow() override;
private slots:
    void on_startServer_clicked();
    void on_startClient_clicked();
private:
    Ui::mainwindow *ui_main;
    std::vector<servergui *> uis_server;
    std::vector<clientgui *> uis_client;
};


#endif //MAINWINDOW_H
