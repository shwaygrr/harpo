// #include "mainwindow.h"
// #include "rsa.h"
#include "aes.h"

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
    // bigint plain_text("112275288879448558774595401684499068783"), priv_key("112197127139048939991993347912889288309");

    // std::bitset<128> plain_text128 = intToBin<128>(plain_text), priv_key128 = intToBin<128>(priv_key);


    // std::bitset<128> cipher_text128 = aesEnc128(binToHex<128>(plain_text128), binToHex<128>(priv_key128));

    // std::cout << binToHex(cipher_text128) << std::endl;


    // std::bitset<128> dec_text128 = aesDec128(binToHex<128>(cipher_text128), binToHex<128>(priv_key128));

    // std::cout << binToHex(dec_text128);
    std::string text = "Hello! My name is Chwoeger Charleston. I'm 27 years old!";
    // std::string text = " !$";

    bigint x = textToInt(text);
    std::cout << x << std::endl;
    std::string y = intToText(x);
    std::cout << y << std::endl;

    return 0;
}
