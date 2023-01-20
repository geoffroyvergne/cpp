#include <iostream>

class ThreadSafeSingleton {
    private:
        static std::unique_ptr<ThreadSafeSingleton> instance;
        static std::once_flag once;
        ThreadSafeSingleton() {} // private constructor
        ThreadSafeSingleton(const ThreadSafeSingleton&) = delete; // copy constructor
        ThreadSafeSingleton& operator=(const ThreadSafeSingleton&) = delete; // assignement operator
    
    public:
        static ThreadSafeSingleton* getInstance();
        void printHelloWorld();
        std::string getHelloWorld();
};
