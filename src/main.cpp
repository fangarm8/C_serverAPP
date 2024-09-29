#include <QApplication>

#include "lib/ui/mainwindow/mainwindow.h"

#include "lib/server/Server.h"
#include "lib/client/Client.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    mainwindow w;
    w.show();
    return QApplication::exec();
}
