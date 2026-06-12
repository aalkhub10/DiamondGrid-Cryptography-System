#include "cipher.hpp"
#include "cryptogrid.hpp"
#include <cstdlib>
#include <string>

using namespace std;


Cipher::Cipher(int seed) : baseSeed(seed) {}

string Cipher::encrypt(const string& message, int rounds) {
    string current = message;
    // Perform encryption over multiple rounds to increase security
    for (int i = 0; i < rounds; ++i) {
        // Seed the random number generator with baseSeed + round number
        // This ensures deterministic but round-unique permutations
        srand(baseSeed + i);
        
        // Create a cryptographic grid and encode the message
        CryptoGrid cg;
        // Calculate grid size based on message length (expanding to diamond shape)
        int size = DiamondGrid::calculateSize(current.length());
        // Create grid structure and populate with current data
        cg.create(size, current);
        // Encrypt by permuting grid contents using seeded random values
        current = cg.encryptToString();
    }
    return current;
}

string Cipher::decrypt(const string& encrypted, int rounds) {
    string current = encrypted;
    // Reverse the encryption process round-by-round
    for (int i = rounds - 1; i >= 0; --i) {
        // Re-seed with the same seed used during encryption (baseSeed + round index)
        // This recreates the original permutation patterns
        srand(baseSeed + i);
        
        // Rebuild the cryptographic grid from encrypted string
        CryptoGrid cg;
        cg.loadFromString(current);
        // Decrypt by reversing permutations, trim padding on final round
        current = cg.extractMessage(i == 0);  // true on last iteration removes padding
    }
    return current;
}
