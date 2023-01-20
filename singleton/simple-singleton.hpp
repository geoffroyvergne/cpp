#include <iostream>

class SimpleSingleton {
    private:
        static SimpleSingleton* instance;
        SimpleSingleton() {} //private constructor
        SimpleSingleton(const SimpleSingleton&) = delete; // copy constructor
        SimpleSingleton& operator=(const SimpleSingleton&) = delete; // assignment operator

    public:
        static SimpleSingleton* getInstance();
        void printHelloWorld();
        std::string getHelloWorld();
};
