#include <iostream>
#include <fstream>
#include "passManager.h"


int main() {
    PassManager pm;

    // Add some test data
    pm.addAccount("example.com", "user1", "pass1");
    pm.addAccount("example.com", "user2", "pass2");
    pm.addAccount("another-site.com", "johndoe", "securepass");

    // Save to file
    pm.savePasswordToFile("passwords.txt", "masterpassword");

    // Verify the file contents
    std::ifstream file("passwords.txt");
    if (file.is_open()) {
        std::string line;
        std::cout << "File contents:" << std::endl;
        while (getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file for reading" << std::endl;
    }

    return 0;
}
