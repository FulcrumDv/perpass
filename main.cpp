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


    return 0;
}
