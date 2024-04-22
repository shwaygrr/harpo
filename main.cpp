#include "rsa.h"
#include "aes.h"

#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("ChCh");
    QCoreApplication::setApplicationName("HarpoChat");
    QCoreApplication::setApplicationVersion("1.0");

    MainWindow* harpo_chat = new MainWindow;

    // Show the intro screen for 3 seconds
    QTimer::singleShot(0, [&]() {
        // After 3 seconds, show the main window
        harpo_chat->show();
    });
    // harpo_chat->show();
    return a.exec();

    return 0;
}

// int main() {

//     std::string message = "Hello! My name is Chwoeger Charleston. I'm 27 years old!";
//     std::string key = "my brother is a cat";

//     //turn message and key to hex
//     std::string message_hex = textToHex(message);
//     std::string key_hex = textToHex(key);

//     //enc 128 bits at a time
//     std::string enc_text = hexToText(encECB128(message_hex, key_hex));
//     std::string enc_hex = textToHex(enc_text);
//     //dec
//     std::string dec_text = hexToText(decECB128(enc_hex, key_hex));
//     std::cout << enc_text << std::endl;;
//     std::cout << dec_text;

//     return 0;
// }
