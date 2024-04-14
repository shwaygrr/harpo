// #include "mainwindow.h"
#include "rsa.h"
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
        bigint a("100010012030403020500503304034505");

        std::cout << modExp(2, 4, 100);
        return 0;
}
