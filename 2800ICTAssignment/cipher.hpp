#ifndef CIPHER_H
#define CIPHER_H

#include <string>

extern const int SEED; 

class Cipher {
private:
    int baseSeed;
public:
    Cipher(int seed = SEED);
    std::string encrypt(const std::string& message, int rounds);
    std::string decrypt(const std::string& encrypted, int rounds);
};

#endif
