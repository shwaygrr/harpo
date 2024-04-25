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
    harpo_chat->setWindowTitle("HarpoChat");
    harpo_chat->show();

    // std::string plain = "hi";

    // std::string hex = textToHex(plain);

    // std::string cipher_hex = encECB128(hex, "02");

    // std::string cipher = hexToText(cipher_hex);

    // std::string back = textToHex(cipher);

    // std::string cipher_dec = decECB128(back, "02");

    // std::cout << hex << std::endl;
    // std::cout << cipher_hex << std::endl;
    // std::cout << cipher << std::endl;
    // std::cout << cipher_dec << std::endl;

    return a.exec();
}
