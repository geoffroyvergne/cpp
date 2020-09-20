#include <iostream>
#include <vector>

int main() {
    std::vector<int> v1;

    for (int i = 1; i <= 10; i++) {
        v1.push_back(i * 10);
    }

    std::cout << "Reference operator [g] : v1[2] = " << v1[2] << std::endl; 
    std::cout << "At v1.at(4) = " << v1.at(4) << std::endl;    
    std::cout << "Front v1.front() = " << v1.front() << std::endl;
    std::cout << "Front v1.back() = " << v1.back() << std::endl; 

    // Point to the first element
    int* pos = v1.data();

    std::cout << "The first element is " << *pos << std::endl;

    return 0;
}
