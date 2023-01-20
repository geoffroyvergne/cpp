#include <iostream>
#include "simple-singleton.hpp"

SimpleSingleton* SimpleSingleton::getInstance() {
    if(!SimpleSingleton::instance) {
        SimpleSingleton::instance = new SimpleSingleton();
    }
    return instance;
}

void SimpleSingleton::printHelloWorld() {
    std::cout << "Simple singleton Hello World!" << std::endl;
}

std::string SimpleSingleton::getHelloWorld() {
    return "Simple singleton Hello World!";
}

SimpleSingleton* SimpleSingleton::instance = nullptr;

/*int main(void) {
    std::cout << "Simple singleton Hello World!" << std::endl;
    SimpleSingleton* singleton = SimpleSingleton::getInstance();
    singleton->printHelloWorld();
    std::cout << SimpleSingleton->getHelloWorld() << std::endl;

    return 0;
}*/
