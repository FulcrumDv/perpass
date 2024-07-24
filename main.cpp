#include "passManager.h"

int main() {
    PassManager pm;
    std::string masterPass = "rbxPQNJyQ8iYDqAaS6wQFE7yYwdPvySc";

    // Add some test data
    pm.addAccount("example.com", "user1", "pass1");
    pm.addAccount("example.com", "user2", "pass2");
    pm.addAccount("another-site.com", "johndoe", "securepass");

    // Save to file
    pm.savePasswordToFile("passwords.txt", masterPass);

    // Clear the accounts and load from file
    pm.loadPasswordsFromFile("passwords.txt", masterPass);

    // View all passes
    pm.viewAllPasses(masterPass);

    return 0;
}
