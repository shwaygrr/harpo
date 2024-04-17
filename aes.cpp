#include "aes.h"

//helper functions


/*
    Binary multiplacation using Galois Field
        Input: 2 Hex values one 4 bit and other 8 bits
        Ouput: Porduct using G(2^3)
*/
std::bitset<8> gfMult(const std::string& mix_hex, const std::string& state_hex) {
    std::bitset<8> mix8(hexToBin<8>(mix_hex)), state8(hexToBin<8>(state_hex));

    if(mix_hex == "01") {
        return hexToBin<8>(state_hex);
    }
    //map to polynomials
    std::vector<int> mix_poly;//length should only be at most  2

    std::vector<int> state_poly;

    for(int i = 0; i < 8; i++) {
        if (mix8[i] == 1) mix_poly.push_back(i);
        if (state8[i] == 1) state_poly.push_back(i);
    }

    //distribution
    std::set<int> product_poly;
    const std::vector<int>irreducible_poly = {4, 3, 1, 0};
    //distrubute
    for(int i = 0; i < mix_poly.size(); i++) {
        // std::cout << mix_poly[i] << "*(";
        for (int j = 0; j < state_poly.size(); j++) {
            // std::cout << state_poly[j] << "+";
            if(product_poly.find(state_poly[j] + mix_poly[i]) != product_poly.end()) {
                product_poly.erase(product_poly.find(state_poly[j] + mix_poly[i])); //erase all instances if exist
            } else { //insert
                //check if 8
                if (state_poly[j] + mix_poly[i] == 8) {
                    for (int k = 0; k < 4; k++) {
                        if(product_poly.find(irreducible_poly[k]) != product_poly.end()) {
                            product_poly.erase(product_poly.find(irreducible_poly[k]));
                        } else {
                            product_poly.insert(irreducible_poly[k]);
                        }
                    }
                } else {
                    product_poly.insert(state_poly[j] + mix_poly[i]);
                }
            }
        }
        // std::cout << ")" << std::endl;
    }

    //set bits
    std::bitset<8> answer;
    for(const int& bit: product_poly) answer[bit] = 1;

    return answer;

    // for(const int& x: product_poly) {
    //     std::cout << x << " ";
    // }
    // std::cout << std::endl << binToInt<8>(answer)<< std::endl;
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
    byteSub<32>(word_32, SBOX);

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

    // for (const std::string& key: keys) {
    //     std::cout << key << std::endl;
    // }

    return keys;
}


//round functions
/*
    Create Matrix
        -Input: hex string
        -Output: basically flipped matrix
*/
std::string flipMatrix(const std::string& hex_str) {
    std::string hex_matrix;

    for(int i = 0; i < 8; i+=2) {
        for (int  j = i; j <= i+24; j+=8) {
            hex_matrix += hex_str.substr(j, 2);
            // std::cout << j << " ";
        }
        // std::cout <<std::endl;
    }
    return hex_matrix;
}


/*
    Add Round Key
        -Input: 128 block of Plaintext and key0
        -Output: Plaintext xor key0
*/
std::bitset<128> addRoundKey(const std::string& plain_text_hex, const std::string& key_hex) {

    std::bitset<128> plain_text128(hexToBin<128>(plain_text_hex));
    std::bitset<128> key128(hexToBin<128>(key_hex));

    return plain_text128 ^ key128;
}

/*
    Shift rows
        Input: 128-bit binary
        Output: Four rows shifted cyclically to the left by offsets of 0,1,2, and 3
*/
void shiftRows(std::bitset<128>& bin128) {
    //split into words
    std::string str = bin128.to_string();
    std::bitset<32> word0_32(str.substr(0, 32)),
                    word1_32(str.substr(32, 32)),
                    word2_32(str.substr(64, 32)),
                    word3_32(str.substr(96, 32));

    word1_32 = (word1_32 << 8) | (word1_32 >> (32 - 8));
    word2_32 = (word2_32 << (8 * 2)) | (word2_32 >> (32 - 8 * 2));
    word3_32 = (word3_32 << (8 * 3)) | (word3_32 >> (32 - 8 * 3));

    std::bitset<128> result(word0_32.to_string() + word1_32.to_string() + word2_32.to_string() + word3_32.to_string());

    bin128 = result;
    // std::cout << binToHex(result);

}

/*

*/
/*
    Mix Column
       -Input:
        -Output:
*/
void mixColumn(std::bitset<128>& bin128) {

    // represent as matrix
    std::vector<std::vector<std::string>> hex_matrix;

    for(int i = 0; i < bin128.size(); i+=32) {
        std::bitset<32> byte_i(bin128.to_string().substr(i, 32));
        std::string word = binToHex(byte_i);

        std::vector<std::string> row;
        for(int j = 0; j < 8; j+=2){
            row.push_back(word.substr(j, 2));
        }
        hex_matrix.push_back(row);
    }

    std::string result_hex;
    //matrix mult
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::bitset<8> col;
            for (int k = 0; k < 4; k++) {
                col ^= gfMult(MIX[i][k], hex_matrix[k][j]); //perform the multiplication and XOR operation
            }
            result_hex += (binToHex<8>(col));
        }
    }

    bin128 = hexToBin<128>(result_hex);
}

//encryption
std::bitset<128> aesEnc128(const std::string& plain_text, const std::string& priv_key) {
    std::cout << "beginning encryption..." << std::endl;
    //generate keys
    std::vector<std::string> round_keys_hex = keyGen(priv_key);

    //create matrices
    std::string plain_text_matrix = flipMatrix(plain_text);
    std::string round_key_matrix = flipMatrix(round_keys_hex[0]);

    //add round with key0
    std::bitset<128> state_matrix128 = addRoundKey(plain_text_matrix, round_key_matrix);


    // 10 round enc
    for(int i = 1; i <= 10; i++) {
        byteSub(state_matrix128, SBOX);
        shiftRows(state_matrix128);
        //skip mixColumn last round
        if (i != 10) mixColumn(state_matrix128);

        state_matrix128 = addRoundKey(binToHex<128>(state_matrix128), flipMatrix(round_keys_hex[i]));
    }

    //flip matrix
    std::bitset<128> cipher_text128 = hexToBin<128>(flipMatrix(binToHex<128>(state_matrix128)));
    //return cipher text
    return cipher_text128;
}
