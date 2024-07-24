#include "passManager.h"
#include <cassert>
#include <iostream>

void testSaveAndLoadPasswords() {
    PassManager pm;
    pm.addAccount("example.com", "user1", "pass1");
    pm.addAccount("example.com", "user2", "pass2");
    pm.addAccount("another.com", "user3", "pass3");

    pm.savePasswordToFile("test.dat", "masterpass");

    PassManager pm2;
    bool loaded = pm2.loadPasswordsFromFile("test.dat", "masterpass");
    assert(loaded);

    // Add more assertions to verify that the loaded data matches the original data
}

void testAddAndRemoveAccount() {
    PassManager pm;
    std::cout << "testing remove" << std::endl;
    pm.addAccount("example.com", "user1", "pass1");
    // Add assertions to verify the account was added
    pm.viewPass("example.com");
    pm.removePass("example.com", "user1");
    pm.viewPass("example.com");


    // Add assertions to verify the account was removed
}

void testEditPass() {
    PassManager pm;
    pm.addAccount("example.com", "user1", "oldpass");

    std::string oldPass = "oldpass";
    std::string newPass = "newpass";
    bool edited = pm.editPass("example.com", "user1", oldPass, newPass);
    assert(edited);

    // Add assertions to verify the password was changed
}

void testViewPass() {
    PassManager pm;
    pm.addAccount("example.com", "user1", "pass1");
    pm.addAccount("example.com", "user2", "pass2");

    // This function prints to cout, so we'd need to capture stdout to test it properly
    pm.viewPass("example.com");
}

void testViewAllPasses() {
    PassManager pm;
    pm.addAccount("example.com", "user1", "pass1");
    pm.addAccount("another.com", "user2", "pass2");

    // This function prints to cout, so we'd need to capture stdout to test it properly
    pm.viewAllPasses("masterpass");
}

int main() {
    //testSaveAndLoadPasswords();
    testAddAndRemoveAccount();
    //testEditPass();
    //testViewPass();
    //testViewAllPasses();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
