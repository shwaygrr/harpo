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
    // bigint x("112197127139048939991993347912889288309");
    // std::bitset<128> xbin(intToBin(x));

    // bigint y("112275288879448558774595401684499068783");
    // std::bitset<128> ybin(intToBin(y));

    //key addition
    // std::bitset<128> start = addRoundKey(binToHex(ybin), binToHex(xbin));

    // //byte sub
    // byteSub<128>(start, SBOX);


    // //shift row
    // shiftRows(start);

    // //mix column
    // mixColumn(start);

    bigint plain_text("112275288879448558774595401684499068783"), priv_key("112197127139048939991993347912889288309");

    std::bitset<128> plain_text128 = intToBin<128>(plain_text), priv_key128 = intToBin<128>(priv_key);


    std::bitset<128> cipher_text128 = aesEnc128(binToHex<128>(plain_text128), binToHex<128>(priv_key128));

    std::cout << binToHex(cipher_text128) << std::endl;


    std::bitset<128> dec_text128 = aesDec128(binToHex<128>(cipher_text128), binToHex<128>(priv_key128));

    std::cout << binToHex(dec_text128);

    // gf8Mult("0F", "FF");

    // std::cout << hexToBin<8>("08");
    return 0;
}
