//
// Created by pavel on 28.09.24.
//

#ifndef CLIENTGUI_H
#define CLIENTGUI_H

#include <QWidget>

#include "../../client/Client.h"
#include "../../client_thread/client_thread.h"


QT_BEGIN_NAMESPACE
namespace Ui { class clientgui; }
QT_END_NAMESPACE

class clientgui : public QWidget {
Q_OBJECT

public:
    explicit clientgui(QWidget *parent = nullptr);
    ~clientgui() override;

private slots:
    void on_ConnectButton_clicked();

private:
    Ui::clientgui *ui;
    Client * client;
    client_thread * cthread;
};


#endif //CLIENTGUI_H
