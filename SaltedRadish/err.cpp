#include "err.h"
#include <iostream>

void fatalError(const std::string& errorString) {
    std::cout << errorString << std::endl;
    std::cout << "lol ur fucked";
    int tmp;
    std::cin >> tmp;
    exit(1);
}
