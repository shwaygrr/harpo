#include "rsa.h"

//helper function

/*
    Modular Exponentiation
        -Input: Base, Exponent, and Modulus
        -Output Base^Exponent mod Modulus
*/
bigint modExp(const bigint& base, bigint exp, const bigint& modulus) {
    bigint result = 1;

    if (exp == 0) return result;

    bigint A = base;

    if (exp % 2 == 1) {
        result = base;
    }

    exp /= 2;

    while (exp != 0) {
        A = (A*A) % modulus;

        if (exp % 2 == 1) result = (A*result) % modulus;

        exp /= 2; //next bit
    }

    return result;
}
