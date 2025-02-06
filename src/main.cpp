#include <iostream>

#include "./http/http.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    startServer();

    std::cout << "Hello, World2!" << std::endl;

    return 0;
}
