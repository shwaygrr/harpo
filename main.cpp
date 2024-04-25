#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QTimer>
#include "aes.h"
#include "rsa.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("ChCh");
    QCoreApplication::setApplicationName("HarpoChat");
    QCoreApplication::setApplicationVersion("1.0");

    MainWindow* harpo_chat = new MainWindow;

    harpo_chat->show();

    return a.exec();
}
