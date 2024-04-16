// #include "mainwindow.h"
// #include "rsa.h"
#include "aes.h"
#include <iostream>
// #include <QApplication>

// int main(int argc, char *argv[])
// {
//     // QApplication a(argc, argv);
//     // MainWindow w;
//     // w.show();
//     // return a.exec();

//     bigint a("100010012030403020500503304034505");

//     std::cout << a;
//     return 0;
// }

int main() {
    // bigint a("100010012030403020500503304034505");
    //128 bits int conversion not supported so must input as binary string
    bigint x("112197127139048939991993347912889288309");
    std::bitset<128> bin(intToBin(x));
    keyGen(binToHex(bin));
    return 0;
}
