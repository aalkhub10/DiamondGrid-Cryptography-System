#include "utils.hpp"
#include <iostream>
#include <sstream>

using namespace std;

// Fixed seed for deterministic encryption/decryption operations
const int SEED = 12345;

// Robust integer input validation with range checking
int getValidatedInt(const string& prompt, int min, int max) {
    int val;
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);

        // Empty input check
        if (line.empty()) {
            cout << "Input cannot be empty. Please try again.\n";
            continue;
        }

        // Full input validation using stringstream
        stringstream ss(line);
        if (ss >> val && ss.eof() && val >= min && val <= max) {
            return val;  // Only return valid complete integer parses
        }

        // Dynamic error message based on input constraints
        cout << "Invalid input. Please enter a valid number";
        if (min != INT_MIN && max != INT_MAX) {
            cout << " (" << min << " - " << max << ")";  // Show range if specified
        }
        cout << ".\n";
    }
}

// Ensures user provides non-blank input for critical fields
string getNonEmptyLine(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (!input.empty()) return input;  // Accept any non-empty string
        cout << "Input cannot be empty. Please try again.\n";
    }
}
