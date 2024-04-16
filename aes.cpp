#include "aes.h"

//helper functions
/*
    Integer to Binary
        Input: Integer
        Output: Binary representation
*/
std::string intToBin(bigint integer) {
    std::string result;

    while(integer != 0 ) {
        result = (integer % 2).as_str() + result;
        integer /= 2;
    }
    // std::cout << result;
    return result;
}


//key generation
/*
    g function for word3 in sub key generation (helper function for key generation)
        Input: 32-bit word
        Output: 32-bit word to xor with word1
*/
std::bitset<32> g32(std::bitset<32> word_32, unsigned int round) {
    //1 byte shift left
    word_32 = (word_32 << 8) | (word_32 >> (32 - 8));

    //byte substition
    word_32 = byteSub<32>(word_32, SBOX);
    // std::cout << word_32;

    //xor with round constant
    word_32 = word_32 ^= hexToBin<32>(ROUND_CONSTANTS[round] + "000000");

    // std::cout << binToHex<32>(word_32) << std::endl;
    return word_32;
}


/*
    Subkey generation
        Input: Previous subkey, k_(i-1) as hex
        Ouput: Subkey, k_i as hex
*/
std::string roundKey128(const std::string& prev_key_hex, unsigned int round) {
    std::bitset<128> prev_key128(hexToBin<128>(prev_key_hex));

    //split into words
    std::string prev_key_str128 = prev_key128.to_string();
    std::bitset<32> word0_32(prev_key_str128.substr(0, 32)),
                    word1_32(prev_key_str128.substr(32, 32)),
                    word2_32(prev_key_str128.substr(64, 32)),
                    word3_32(prev_key_str128.substr(96, 32));

    // std::cout << "word0: " << binToHex<32>(word0_32) << std::endl;
    // std::cout << "word1: " << binToHex<32>(word1_32) << std::endl;
    // std::cout << "word2: " << binToHex<32>(word2_32) << std::endl;
    // std::cout << "word3: " << binToHex<32>(word3_32) << std::endl;

    //get next words
    std::bitset<32> next_word0_32 = (word0_32 ^= g32(word3_32, round));
    std::bitset<32> next_word1_32 = (next_word0_32 ^ word1_32);
    std::bitset<32> next_word2_32 = (next_word1_32 ^ word2_32);
    std::bitset<32> next_word3_32 = (next_word2_32 ^ word3_32);

    std::bitset<128> key_i128(next_word0_32.to_string() + next_word1_32.to_string() + next_word2_32.to_string() + next_word3_32.to_string());

    return binToHex<128>(key_i128);
}


/*
    Key Generation
        Input: First key as hex
        Output: 10 round keys as hes
*/
std::vector<std::string> keyGen(const std::string& key_hex) {
    std::vector<std::string> keys = {key_hex};

    for(int i = 1; i <= 10; i++) {
        std::string key_i = roundKey128(keys[i-1], i-1);
        keys.push_back(key_i);
    }

    for (const std::string& key: keys) {
        std::cout << key << std::endl;
    }

    return keys;
}
