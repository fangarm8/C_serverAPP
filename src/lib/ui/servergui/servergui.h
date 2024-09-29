//
// Created by pavel on 28.09.24.
//

#ifndef SERVERGUI_H
#define SERVERGUI_H

#include <QWidget>

#include "../../server/Server.h"
#include "../../server_thread/server_thread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class servergui; }
QT_END_NAMESPACE

class servergui : public QWidget {
Q_OBJECT

public:
    explicit servergui(QWidget *parent = nullptr);
    ~servergui() override;
private:
    Ui::servergui * ui;
    Server * server;
    server_thread * sthread;
};


#endif //SERVERGUI_H
