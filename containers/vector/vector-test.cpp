#include <iostream>
#include <vector>

int main() {
    std::vector<int> v1;

    for (int i=1; i <= 5; i++) {
        v1.push_back(i);
    }

    std::cout << "Output of begin and end : " << std::endl;
    for (auto i = v1.begin(); i != v1.end(); i++) {
        std::cout << *i << " " << std::endl;
    }

    std::cout << "Output of cbegin and cend : " << std::endl;
    for (auto i = v1.cbegin(); i != v1.cend(); i++) {
        std::cout << *i << " " << std::endl;
    }

    std::cout << "Output of rbegin and end : " << std::endl;
    for (auto i = v1.rbegin(); i != v1.rend(); i++) {
        std::cout << *i << " " << std::endl;
    }

    std::cout << "Output of crbegin and cend : " << std::endl;
    for (auto i = v1.crbegin(); i != v1.crend(); i++) {
        std::cout << *i << " " << std::endl;
    }

    return 0;
}
