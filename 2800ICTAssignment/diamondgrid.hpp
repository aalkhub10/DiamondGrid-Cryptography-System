#ifndef DIAMONDGRID_HPP
#define DIAMONDGRID_HPP

#include <vector>

class DiamondGrid {
private:
    std::vector<int> rows, cols;
    void computePositions(int n);
public:
    static int calculateSize(int msgLength);
    void generate(int n);
    int positionsCount() const;
    const std::vector<int>& getRows() const;
    const std::vector<int>& getCols() const;
};

#endif // DIAMONDGRID_HPP
