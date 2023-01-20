#include <iostream>
#include "tread-safe-singleton.hpp"

ThreadSafeSingleton* ThreadSafeSingleton::getInstance() {
    std::call_once(once, []() {
        ThreadSafeSingleton::instance.reset(new ThreadSafeSingleton());
    });
    return ThreadSafeSingleton::instance.get();
}

void ThreadSafeSingleton::printHelloWorld() {
    std::cout << "Thread safe singleton Hello World!" << std::endl;
}

std::string ThreadSafeSingleton::getHelloWorld() {
    return "Thread safe singleton Hello World!";
}

std::unique_ptr<ThreadSafeSingleton> ThreadSafeSingleton::instance;
std::once_flag ThreadSafeSingleton::once;

/*int main(void) {
    std::cout << "Thread safe singleton Hello World!" << std::endl;
    ThreadSafeSingleton* singleton = ThreadSafeSingleton::getInstance();
    singleton->printHelloWorld();
    std::cout << singleton->getHelloWorld() << std::endl;

    return 0;
}*/
