#include "diamondgrid.hpp"
#include <cmath>

using namespace std;

// Core diamond pattern generation algorithm
void DiamondGrid::computePositions(int n) {
    rows.clear();
    cols.clear();
    int mid = n / 2;  // Center point of the grid (works for odd sizes)

    // Diamond grows symmetrically from center row
    for (int row = 0; row < n; ++row) {
        int distance = abs(mid - row);  // Vertical distance from center
        int start_col = mid - distance; // Left boundary for diamond in this row
        int end_col = mid + distance;   // Right boundary for diamond in this row
        
        // Create horizontal diamond segment for current row
        for (int col = start_col; col <= end_col; ++col) {
            rows.push_back(row);
            cols.push_back(col);
        }
    }
}

// Finds minimal odd-sized grid that can contain message
int DiamondGrid::calculateSize(int msgLength) {
    int n = 1;  // Start with smallest possible diamond (size 1x1)
    while (true) {
        DiamondGrid temp;
        temp.generate(n);  // Test candidate size
        // Check if diamond has enough positions to hold message
        if (temp.positionsCount() >= msgLength) return n;
        n += 2; // Only odd sizes ensure symmetrical diamond with single center row
    }
}

// Public interface to generate diamond pattern for given grid size
void DiamondGrid::generate(int n) {
    computePositions(n);  // Delegates to core algorithm
}

// Total available positions in diamond pattern
int DiamondGrid::positionsCount() const {
    return rows.size();  // Each coordinate pair counts as one position
}

// Accessors for diamond coordinates
const vector<int>& DiamondGrid::getRows() const { return rows; }
const vector<int>& DiamondGrid::getCols() const { return cols; }
