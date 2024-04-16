#ifndef AES_H
#define AES_H

#include "bigint.h"
#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include <vector>

//tables
extern const std::vector<std::vector<std::string>> SBOX;
extern const std::vector<std::string> ROUND_CONSTANTS;
//helper funtions
/*
    Binary to Decimal
        Input: Binary
        Output: Decimal representation
*/
template<size_t bit_size>
bigint binToInt(const std::bitset<bit_size>& bin) {
    bigint result;

    for (int i = 0; i < bit_size; i++) {
        result += big_pow(2*bin[i], i);;
    }
    // std::cout << result;
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

std::string intToBin(bigint integer);

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

        std::string int_value_bin = intToBin(int_value);

        //pad
        while(int_value_bin.size() != 4) int_value_bin  = "0" + int_value_bin;

        result_str += int_value_bin;
    }

    //int to binary
    std::bitset<bit_size> result(result_str);
    return result;
}

//key generation
std::bitset<32> g32(std::bitset<32> word_32, unsigned int round);
std::string roundKey128(const std::string& prev_key_hex, unsigned int round);
std::vector<std::string> keyGen(const std::string& key_hex);

//round functions
template<size_t bit_size>
std::bitset<bit_size>byteSub(std::bitset<bit_size> bin, std::vector<std::vector<std::string>> table) {
    //get as hex
    std::string hex_rep = binToHex(bin);

    std::string hex_result = "";

    for(int i = 0; i < hex_rep.size(); i+=2) {
        std::string prev_byte = hex_rep.substr(i, 2);

        //get row and column
        unsigned int row, col;
        std::stringstream row_ss, col_ss;
        row_ss << std::hex << prev_byte[0]; col_ss << std::hex << prev_byte[1];
        row_ss >> row; col_ss >> col;

        hex_result += table[row][col];
    }
    // std::cout << hexToBin<bit_size>(hex_result);

    //turn to binary and return
    return hexToBin<bit_size>(hex_result);
}

//encryption


//inverse round functions


//decryption


#endif // AES_H