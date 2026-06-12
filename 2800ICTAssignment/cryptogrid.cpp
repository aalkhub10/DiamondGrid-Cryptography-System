#include "cryptogrid.hpp"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

// Generates pseudorandom uppercase character using seeded rand()
char CryptoGrid::randomChar() {
    return 'A' + rand() % 26; // Depends on srand() seeding from Cipher class
}

// Creates diamond-shaped grid and embeds message in diamond pattern
void CryptoGrid::create(int size, const string& message) {
    diamondPattern.generate(size); // Generate diamond coordinate system
    const auto& rows = diamondPattern.getRows();
    const auto& cols = diamondPattern.getCols();

    grid.resize(size, vector<char>(size));
    vector<vector<bool>> isDiamond(size, vector<bool>(size, false)); // Tracks diamond positions

    int msgIndex = 0;
    // Fill diamond positions with message + random padding
    for (size_t i = 0; i < rows.size(); ++i) {
        int r = rows[i];
        int c = cols[i];

        // Safety check for invalid diamond coordinates
        if (r >= size || c >= size) {
            cerr << "Invalid position: (" << r << "," << c << ") for size " << size << endl;
            exit(1);
        }

        isDiamond[r][c] = true;
        // Insert message character or random padding if message ends
        grid[r][c] = (msgIndex < message.size()) ? message[msgIndex++] : randomChar();
    }

    // Fill non-diamond positions with random characters
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (!isDiamond[i][j]) {
                grid[i][j] = randomChar();
            }
        }
    }
}

// Serializes grid by reading columns top-to-bottom, left-to-right
string CryptoGrid::encryptToString() const {
    string encrypted;
    int n = grid.size();
    // Transpose grid (columns become rows) to obscure message
    for (int col = 0; col < n; ++col) {
        for (int row = 0; row < n; ++row) {
            encrypted += grid[row][col];
        }
    }
    return encrypted;
}

// Reconstructs grid from encrypted string's column-wise format
void CryptoGrid::loadFromString(const string& encrypted) {
    int n = sqrt(encrypted.size()); // Grid is always square
    grid.resize(n, vector<char>(n));
    diamondPattern.generate(n); // Regenerate original diamond pattern
    
    // Rebuild grid by columns (reverse of encryptToString)
    int idx = 0;
    for (int col = 0; col < n; ++col) {
        for (int row = 0; row < n; ++row) {
            grid[row][col] = encrypted[idx++];
        }
    }
}

// Extracts message from diamond pattern, optionally trimming padding
string CryptoGrid::extractMessage(bool stripDot) const {
    const auto& rows = diamondPattern.getRows();
    const auto& cols = diamondPattern.getCols();
    string decrypted;

    // Reconstruct message from diamond coordinates
    for (size_t i = 0; i < rows.size(); ++i) {
        decrypted += grid[rows[i]][cols[i]];
    }

    // Remove characters after first '.' if requested (final decryption step)
    if (stripDot) {
        size_t dotPos = decrypted.find('.');
        if (dotPos != string::npos) {
            decrypted = decrypted.substr(0, dotPos);
        }
    }

    return decrypted;
}

// Standard accessor for grid dimensions
int CryptoGrid::getSize() const {
    return grid.size();
}

// Debugging utility to visualize grid contents
void CryptoGrid::display() const {
    for (const auto& row : grid) {
        for (char ch : row) {
            cout << ch << ' ';
        }
        cout << '\n';
    }
}
