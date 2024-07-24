#include "utilities.h"
#include <iostream>
#include <string>
#include <random>

std::string Utilities::generateMasterKey(){
    const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::random_device re;
    std::mt19937_64 mt(re());
    std::uniform_int_distribution<int> dist(0, chars.size() - 1);

    std::string key;
    for(int i = 0; i < 256; ++i){
        key += chars[dist(mt)];
    }

    return key;
}
