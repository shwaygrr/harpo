#ifndef RSA_H
#define RSA_H

#include "bigint.h"

#include <iostream>
#include <string>
#include <random>   // For random number generation

//helper functions
bigint modExp(const bigint& base, bigint exp, const bigint& modulus);
bigint binaryToDecimal(const std::string& binary_str);
bigint randOddNumGen(unsigned int size);
bigint randNumGen(const int min, const bigint& max);
bool millerRabin(const bigint& odd_num, unsigned int t);
bigint gcd(const bigint &a, const bigint& b);
bigint EEA(bigint a, bigint b);

//key gen
bigint randPrimeGen(unsigned int size);
void keyGen(unsigned int bit_size);

//encryption
bigint rsaEnc(const bigint& plain_text, const bigint& e_pub_key, const bigint& n_pub_key);

//decryption
bigint rsaDec(const bigint& cipher_text, const bigint& priv_key, const bigint& n_pub_key);



//keys
extern bigint n_public;
extern bigint e_public;
extern bigint d_private;
#endif // RSA_H
