#ifndef CONVERSION_H
#define CONVERSION_H

#include "bigint.h"
#include <iostream>
#include <bitset>

/*
    Binary to Decimal
        Input: Binary
        Output: Decimal representation
*/
template<size_t bit_size>
bigint binToInt(const std::bitset<bit_size>& bin) {
    bigint result = 0;

    for (int i = 0; i < bit_size; i++) {
        if (bin[i]) {
            result += big_pow(2, i); // Assuming big_pow is defined somewhere
        }
    }

    return result;
}


/*
    Binary to Hexadecimal
        - Input: binary
        - Output: hexadecimal representation
*/
template<size_t bit_size>
std::string binToHex(const std::bitset<bit_size>& bin) {
    std::string bin_str = bin.to_string();

    //pad
    while (bin_str.size() % 4 != 0) bin_str = "0" + bin_str;

    std::string hex_str;

    //hex chunks of 4 bits
    for (int i = 0; i < bin_str.size(); i += 4) {
        // Extract a chunk of 4 bits from the binary number
        std::bitset<4> chunk(bin_str.substr(i, 4));

        //chunk to decimal
        char hex_digit = chunk.to_ulong() < 10 ? '0' + chunk.to_ulong() : 'A' + chunk.to_ulong() - 10;

        hex_str.push_back(hex_digit);
    }

    // Return the hexadecimal string
    return hex_str;
}


/*
    Integer to Binary
        Input: Integer
        Output: Binary representation
*/
template<size_t bit_size>
std::bitset<bit_size> intToBin(bigint integer) {
    std::string result;

    while(integer != 0) {
        result = (integer % 2).as_str() + result;
        integer /= 2;
    }
    // std::cout << result;
    std::bitset<bit_size> result_bin(result);
    return result_bin;
}


/*
    Hexadecimal to Binary
        - Input: Hexadecimal as string
        - Output: Binary representation
*/
template<size_t bit_size>
std::bitset<bit_size> hexToBin(const std::string& hex) {
    std::string result_str = "";

    //convert to int
    for(const char& hex_letter : hex) {
        //convert to int
        int int_value;
        std::stringstream int_value_ss;
        int_value_ss << std::hex << hex_letter;
        int_value_ss  >> int_value;

        std::string int_value_bin = intToBin<4>(int_value).to_string();

        result_str += int_value_bin;
    }

    //int to binary
    std::bitset<bit_size> result(result_str);
    return result;
}


/*
    Text to Integer
        -Input: Text as string
        -Ouput: Integer as string
*/
inline bigint textToInt(const std::string& text) {
    std::string result;

    for (char c : text) {
        std::string ascii = std::to_string(static_cast<int>(c-32));
        // std::cout << ascii << " ";
        if (ascii.size() == 1)
            result += ("0"+ascii);
        else
            result += (ascii);
    }
    return to_bigint(result);
}


/*
    Integer to Text
        -Input: Integer as string
        -Output: String as Integer
*/
inline std::string intToText(const bigint& integer) {

    std::string int_str = integer.as_str();

    std::string result = "";

    for(int i = 0; i < int_str.size(); i+=2) {
        unsigned int ascii = stoi(int_str.substr(i, 2)) + 32;
        result += static_cast<char>(ascii);
        // std::cout << ascii << ": " << static_cast<char>(ascii) << std::endl;
    }
    return result;
}

inline std::string hexToText(std::string text) {
    //pad text
    while (text.size() % 2 != 0) text = "0" + text;

    std::string result = "";
    for (int i = 0; i < text.size(); i+=2) {
        std::string hex = text.substr(i, 2);

        //turn to int
        std::bitset<8> hex_bin(hexToBin<8>(hex));
        bigint hex_int = binToInt<8>(hex_bin); //might have to add 32

        //int to ascii
        result += static_cast<char>(stoi(hex_int.as_str()));
    }

    //turn every two to decimal and get ascii rep
    return result;
}

inline std::string textToHex(std::string hex) {
    std::string result = "";;

    for (int i = 0; i < hex.size(); i++) {
        //hex to int
        int ascii = static_cast<int>(static_cast<unsigned char>(hex[i]));

        //int to hex
        std::string ascii_hex = binToHex<8>(intToBin<8>(ascii));
        result += ascii_hex;
    }
    return result;
}

#endif // CONVERSION_H
