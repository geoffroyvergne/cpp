#include <iostream>

#ifndef CORE
#define CORE

class NcursesCore {
    private:
        static NcursesCore* instance;
        NcursesCore() {} //private constructor
        //Core();
        NcursesCore(const NcursesCore&) = delete; // copy constructor
        NcursesCore& operator=(const NcursesCore&) = delete; // assignment operator
        WINDOW* window;

    public:
        std::string name = "Game of life";
        void displayMessage(std::string message);
        void init();
        static NcursesCore* getInstance();

        //std::string getStr(int state);

        WINDOW* getWindow();
};

#endif
