#include "menuhandler.hpp"
#include "utils.hpp"
#include "cryptogrid.hpp"
#include "diamondgrid.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

// Preprocesses message: removes spaces and ensures '.' termination for first input
string MenuHandler::checkPrompt(const string& msg, bool isFirst) {
    string input = msg;
    if (isFirst) {
        // Remove all spaces and add terminal '.' if missing
        input.erase(remove(input.begin(), input.end(), ' '), input.end());
        if (!input.empty() && input.back() != '.') input += '.';
    }
    return input;
}

// Handles single-round encryption configuration and execution
void MenuHandler::handleSingleRoundEncryption() {
    int choice;
    do {
        cout << "\nMenu - Level 3 (Single Round)\n"
             << "1. Enter grid size\n"
             << "2. Automatic grid size\n"
             << "3. Print grid and encoded message\n"
             << "4. Back\n";
        choice = getValidatedInt("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1:  // Manual grid size selection
                gridSize = getValidatedInt("Enter grid size (odd number): ", 1);
                if (gridSize % 2 == 0) {  // Enforce odd-sized grids
                    cout << "Grid size must be odd!\n";
                    gridSize = -1;
                }
                break;
            case 2:  // Automatic size calculation based on message length
                gridSize = DiamondGrid::calculateSize(currentMessage.size());
                cout << "Auto-selected grid size: " << gridSize << "\n";
                break;
            case 3:  // Encryption execution and visualization
                if (gridSize <= 0) {
                    cout << "Set grid size first!\n";
                    break;
                }
                srand(SEED);  // Fixed seed for reproducible encryption
                {
                    CryptoGrid cg;
                    cg.create(gridSize, currentMessage);
                    cout << "\nGrid:\n";
                    cg.display();
                    currentMessage = cg.encryptToString();  // Column-wise serialization
                    cout << "\nEncrypted message:\n" << currentMessage << "\n";
                }
                break;
        }
    } while (choice != 4);
}

// Manages multi-round encryption with progress visualization
void MenuHandler::handleMultiRoundEncryption() {
    int totalRounds = 0;
    int choice;
    do {
        cout << "\nMenu - Level 3 (Multi Round)\n"
             << "1. Enter round number\n"
             << "2. Process rounds with details\n"
             << "3. Back\n";
        choice = getValidatedInt("Enter your choice: ", 1, 3);

        switch (choice) {
            case 1:
                totalRounds = getValidatedInt("Enter number of rounds: ", 1);
                break;
            case 2:
                if (totalRounds <= 0) {
                    cout << "Enter round number first!\n";
                    break;
                }
                {
                    string tempMessage = currentMessage;
                    for (int i = 0; i < totalRounds; i++) {
                        srand(SEED + i);  // Sequential seeding for chained encryption
                        CryptoGrid cg;
                        int size = DiamondGrid::calculateSize(tempMessage.size());
                        cg.create(size, tempMessage);
                        tempMessage = cg.encryptToString();
                        cout << "\nRound " << i + 1 << ":\n";
                        cout << "Grid size: " << size << "\n";
                        cg.display();
                        cout << "Encrypted message:\n" << tempMessage << "\n";
                    }
                    currentMessage = tempMessage;
                }
                break;
        }
    } while (choice != 3);
}

// Main encryption workflow controller
void MenuHandler::runEncryptionMenu() {
    currentMessage.clear();
    int choice;
    do {
        cout << "\nMenu - Level 2 (Encryption)\n"
             << "1. Enter message\n"
             << "2. One round encryption\n"
             << "3. Automatic multi-round encryption\n"
             << "4. Back\n";
        choice = getValidatedInt("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1:  // Message input with preprocessing
                currentMessage = getNonEmptyLine("Enter message: ");
                currentMessage = checkPrompt(currentMessage, true);
                break;
            case 2:  // Single-round path
                if (currentMessage.empty()) {
                    cout << "Enter message first!\n";
                    break;
                }
                handleSingleRoundEncryption();
                break;
            case 3:  // Multi-round path
                if (currentMessage.empty()) {
                    cout << "Enter message first!\n";
                    break;
                }
                handleMultiRoundEncryption();
                break;
        }
    } while (choice != 4);
}

// Decryption workflow with round-by-round reversal
void MenuHandler::runDecryptionMenu() {
    encryptedMessage.clear();
    int choice;
    do {
        cout << "\nMenu - Level 2 (Decryption)\n"
             << "1. Enter encrypted message\n"
             << "2. Enter round number\n"
             << "3. Process rounds with details\n"
             << "4. Back\n";
        choice = getValidatedInt("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1:
                encryptedMessage = getNonEmptyLine("Enter encrypted message: ");
                break;
            case 2:
                rounds = getValidatedInt("Enter number of rounds: ", 1);
                break;
            case 3:
                if (encryptedMessage.empty() || rounds <= 0) {
                    cout << "Enter message and rounds first!\n";
                    break;
                }
                {
                    string tempMessage = encryptedMessage;
                    // Reverse encryption process using original seed sequence
                    for (int i = 0; i < rounds; ++i) {
                        srand(SEED + (rounds - 1 - i));  // Reverse seed order
                        CryptoGrid cg;
                        cg.loadFromString(tempMessage);
                        cout << "\nRound " << i + 1 << ":\n";
                        cout << "Grid size: " << cg.getSize() << "\n";
                        cg.display();
                        tempMessage = cg.extractMessage(i == rounds - 1); // Strip padding on last round
                        cout << "Partial decryption: " << tempMessage << "\n";
                    }
                    cout << "Final decrypted message: " << tempMessage << "\n";
                }
                break;
        }
    } while (choice != 4);
}

// Top-level menu controller
void MenuHandler::mainMenu() {
    int choice;
    do {
        cout << "\nMenu - Level 1\n"
             << "1. Encrypt a message\n"
             << "2. Decrypt a message\n"
             << "3. Quit\n";
        choice = getValidatedInt("Enter your choice: ", 1, 3);

        switch (choice) {
            case 1: runEncryptionMenu(); break;  // Enter encryption subsystem
            case 2: runDecryptionMenu(); break;  // Enter decryption subsystem
        }
    } while (choice != 3);
    cout << "Exiting program.\n";
}
