#include "service.h"
#include <iostream>

int main() {
    try {
        Service service;
        service.run();
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
