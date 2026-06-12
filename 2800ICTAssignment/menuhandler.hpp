#ifndef MENUHANDLER_HPP
#define MENUHANDLER_HPP

#include <string>
#include "cipher.hpp"

class MenuHandler {
private:
    Cipher cipher;
    std::string currentMessage;
    std::string encryptedMessage;
    int rounds = 0;
    int gridSize = -1;

    static std::string checkPrompt(const std::string& msg, bool isFirst);
    void handleSingleRoundEncryption();
    void handleMultiRoundEncryption();
public:
    void runEncryptionMenu();
    void runDecryptionMenu();
    void mainMenu();
};

#endif // MENUHANDLER_HPP
