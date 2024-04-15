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

        // std::cout << modExp(2, 4, 100);
        // std::cout << binaryToDecimal("1001");

        // std::cout << randOddNumGen(4);
        // for(int i = 0; i < 2; i++) {
        //     std::cout << randPrimeGen(256) << std::endl;
        // }

        // std::tuple<bigint, bigint> x = EEA(6007800, 3674911);
        // std::cout << std::get<0>(x) << " " << std::get<1>(x);

        keyGen(64);
        std::cout << "e_public: " << e_public << " n_public: " << n_public << " d_private: " << d_private << std::endl;
        return 0;
}
