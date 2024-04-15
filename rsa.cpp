#include "rsa.h"

//keys
bigint n_public, e_public, d_private;

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


/*
    Binary to Decimal
        - Input: binary string
        - Output: large bigint
        https://www.geeksforgeeks.org/program-binary-decimal-conversion/
*/
bigint binaryToDecimal(const std::string& binary_str) {
    bigint dec_value = 0;

    // Initializing base value to 1, i.e 2^0
    bigint base = 1;

    int len = binary_str.length();
    for (int i = len - 1; i >= 0; i--) {
        if (binary_str[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    return dec_value;
}


/*
    Random Odd Number Generator
        - input: bit size, size
        - output: random odd number of bit size, size
        https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
*/
bigint randOddNumGen(unsigned int size) {
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()

    std::uniform_int_distribution<unsigned short int> distrib(0,1);

    // return distrib(gen);
    std::string binary_str = "1";

    // Iterate over the range [0, N - 1]
    for (int i = 0; i < size-2; i++) {
        binary_str += std::to_string(distrib(gen));
    }

    binary_str += "1"; //ensure odd (prime)

    // std::cout << binaryToDecimal(binary_str).as_str().length() << std::endl;
    return binaryToDecimal(binary_str); //converted to int
}


/*
    Random Number Generator
        - input: min and max
        - output: random number between min and max inclusive
        https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
        **implementation can be improved**
*/
bigint randNumGen(const int min, const bigint& max) {
    //error handling
    if (min >= max) {
        throw std::invalid_argument("min must be less than max");
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    //number of bits required to represent max
    std::string max_bit_size = (big_log2(max)+1).as_str();

    //generate a random number within range
    bigint rand_num;

    do {
        std::string binary_str;
        for (int i = 0; i < std::stoi(max_bit_size); i++) {
            binary_str += std::to_string(gen() % 2);
        }
        rand_num = binaryToDecimal(binary_str);
    } while (rand_num < min || rand_num > max);

    return rand_num;
}


/*
    Miller-Rabin primality test
        -Input: ineger (odd number in this case), amout a tests, t
        -Output: boolean for is prime
*/
bool millerRabin(const bigint& odd_num, unsigned int t) {
    if (odd_num <= 1)
        return false;
    if (odd_num <= 3)
        return true;

    //determine the values of s and r such that odd_num - 1 = 2^s * r
    bigint s = 0, r = odd_num - 1;
    while (r % 2 == 0) {
        r /= 2;
        ++s;
    }

    for (unsigned int i = 0; i < t; ++i) {
        bigint rand_num = randNumGen(2, odd_num - 1); //random number in the range [2, odd_num - 1]
        bigint y = modExp(rand_num, r, odd_num);

        if (y != 1 && y != odd_num - 1) {
            bigint j = 1;
            while (j <= s - 1 && y != odd_num - 1) {
                y = modExp(y, 2, odd_num);
                if (y == 1)
                    return false;
                ++j;
            }
            if (y != odd_num - 1)
                return false;
        }
    }
    return true;
}


/*
    Extended Euclidean
        -Input: two non-negative integer a and b : a >= b
        -Output: d = gcd(a, b) and integers x, y satisfying ax + by = d
        **Algorithm from Handbook of Applied Cryptography**
*/
bigint EEA(bigint a, bigint b) {
    bigint d, x, y;

    if (b == 0) {
        d = a; x = 1; y = 0;
        return x;
    }

    bigint x2 = 1, x1 = 0, y2 = 0, y1 = 1;
    while (b > 0) {
        bigint q = a/b;
        bigint r = a - (q*b);
        x = x2 - (q*x1);
        y = y2 - (q*y1);

        a = b; b = r; x2 = x1; x1 = x; y2 = y1; y1 = y;
    }

    d = a; x = x2; y = y2;

    std::cout << d << std::endl;
    if (x > 0) return x; else return y;
    // return {d, x + a};
}


//key generation
/*
    Large Prime Generator
        -Input: bit size, n
        -Output: prime number of bitsize n tested by Miller-Rabin
*/
bigint randPrimeGen(unsigned int size) {
    bigint rand_num;

    do {
        rand_num = randOddNumGen(size);
    } while(millerRabin(rand_num, 50) == false );

    return rand_num;
}


//encryption
/*
    RSA Key Generation
        -Input:
        -Output:
*/
void keyGen(const bigint& message) {
    unsigned int num_bits = std::stoi((big_log2(message) + 1).as_str());

    //generate two large primes
    bigint p = randPrimeGen(num_bits + 1);
    bigint q = randPrimeGen(num_bits + 1);

    //ensure p and q are distinct
    while (p == q) q = randPrimeGen(num_bits + 1);

    //compute n and phi = (p-1)*(q-1)
    n_public = p * q;
    bigint phi = (p - 1) * (q - 1);

    //generate public and private keys
    do {
        //generate random e
        e_public= randNumGen(2, phi - 1);

        //compute inverse
        d_private = EEA(phi, e_public);
    } while ((e_public * d_private) % phi != 1); //check if e*d mod phi = 1

    std::cout << "Verification: " << (d_private * e_public) % phi << std::endl;
}
