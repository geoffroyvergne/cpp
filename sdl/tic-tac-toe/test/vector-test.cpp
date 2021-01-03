#include <iostream>
#include <vector>
#include <unistd.h>

class Test {
    public:
        int code;
        std::string value;
};

int main(int argc, char** argv) {

    std::vector<Test*> testList;

    while(true) {
        for (int i=1; i <= 5; i++) {
            Test *test = new Test();
            test->code = i;
            test->value = "test class";

            testList.push_back(test);
        }

        //testList.clear();
        //testList.resize(0);
        //testList.shrink_to_fit();

        //std::vector<Test*>(testList).swap(testList);
        //std::vector<Test*>().swap(testList);

        //std::vector<Test*> testList;

        for (auto p : testList) {
            delete p;
        } 
        testList.clear();

        //usleep(1000);

        /*for (size_t i = 0; i < testList.size(); ++i) {
            delete(testList[i]);
        }*/

    }


    return EXIT_SUCCESS;
}