#ifndef CRYPTOGRID_HPP
#define CRYPTOGRID_HPP

#include <vector>
#include <string>
#include "diamondgrid.hpp"

class CryptoGrid {
private:
    std::vector<std::vector<char>> grid;
    DiamondGrid diamondPattern;
    static char randomChar();
public:
    void create(int size, const std::string& message);
    std::string encryptToString() const;
    void loadFromString(const std::string& encrypted);
    std::string extractMessage(bool stripDot = true) const;
    int getSize() const;
    void display() const;
};

#endif // CRYPTOGRID_HPP
