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
    bigint plain_text("112275288879448558774595401684499068783"), priv_key("112197127139048939991993347912889288309");

    // std::bitset<128> plain_text128 = intToBin<128>(plain_text), priv_key128 = intToBin<128>(priv_key);
    // std::string enc_hex = encECB128(binToHex<128>(plain_text128), binToHex<128>(priv_key128));
    // std::string enc_text = hexToText(enc_hex);

    // std::string cipher_hex = textToHex(enc_text);
    // std::string dec_hex = decECB128(cipher_hex, binToHex<128>(priv_key128));

    // // std::dec_hex = encECB128(binToHex<128>(intToBin<128>(plain_text)), binToHex(intToBin<128>(priv_key)))
    // // stf:: dec_text = encECB128(binToHex<128>(intToBin<128>(plain_text)), binToHex(intToBin<128>(priv_key)))
    // std::cout << binToHex<128>(plain_text128) << std::endl;
    // std::cout << enc_hex << std::endl;
    // std::cout << enc_text << std::endl;
    // std::cout << cipher_hex << std::endl;
    // std::cout << dec_hex << std::endl;
    // std::cout << textToInt(x) << std::endl;
    // std::string plai_hex =

    // std::bitset<128> cipher_text128 = aesEnc128(binToHex<128>(plain_text128), binToHex<128>(priv_key128));

    // std::cout << binToHex(cipher_text128) << std::endl;


    // std::bitset<128> dec_text128 = aesDec128(binToHex<128>(cipher_text128), binToHex<128>(priv_key128));

    // std::cout << binToHex(dec_text128);
    std::string message = "Hello! My name is Chwoeger Charleston. I'm 27 years old!";
    std::string key = "my brother is a cat";

    //turn message and key to hex
    std::string message_hex = textToHex(message);
    std::string key_hex = textToHex(key);

    //enc 128 bits at a time
    std::string enc_text = hexToText(encECB128(message_hex, key_hex));

    //dec
    std::string dec_text = hexToText(decECB128(textToHex(enc_text), key_hex));
    std::cout << enc_text << std::endl;;
    std::cout << dec_text;

    // std::string dec_hex = decECB128(enc_hex, key_hex);
    // std::string message_hex = binToHex<128>(intToBin<128>(textToInt(message)));
    // std::string key_hex = binToHex<128>(intToBin<128>(textToInt(key)));

    // std::string cipher_hex = encECB128(message_hex, key_hex);

    // std::cout << "cipher text: " << intToText(binToInt<128>(hexToBin<128>(cipher_hex))) << std::endl;

    // std::string plain_hex = decECB128(cipher_hex, key_hex);

    // std::cout << "plain text: " << intToText(binToInt<128>(hexToBin<128>(plain_hex))) << std::endl;

    // std::string text = " !$";

    // bigint x = textToInt(text);
    // std::cout << x << std::endl;
    // std::string y = intToText(x);
    // std::cout << y << std::endl;
    // std::bitset<8>x("1000");
    // std::cout << binToHex<8>(x);
    // std::string hex = hexToText("195");
    // std::string x = textToHex(hex);
    return 0;
}
