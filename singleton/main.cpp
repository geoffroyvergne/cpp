#include <iostream>
#include "simple-singleton.hpp"
#include "tread-safe-singleton.hpp"

int main(void) {
    std::cout << "Simple singleton Hello World!" << std::endl;
    SimpleSingleton::getInstance()->printHelloWorld();
    std::cout << SimpleSingleton::getInstance()->getHelloWorld() << std::endl;

    std::cout << "" << std::endl;

    std::cout << "Thread safe singleton Hello World!" << std::endl;
    ThreadSafeSingleton::getInstance()->printHelloWorld();
    std::cout << ThreadSafeSingleton::getInstance()->getHelloWorld() << std::endl;

    return EXIT_SUCCESS;
}
