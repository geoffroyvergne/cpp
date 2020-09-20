#include <iostream>
#include <vector>

int main() {
    std::vector<int> v1;

    for (int i=1; i <= 5; i++) {
        v1.push_back(i);
    }

    std::cout << "Size : " << v1.size() << std::endl;
    std::cout << "Capacity : " << v1.capacity() << std::endl;
    std::cout << "Max size : " << v1.max_size() << std::endl;

    // Resize the size vector to 4
    v1.resize(4);

    // prints vector size after resize()
    std::cout << "Size : " << v1.size() << std::endl;

    // check if the vector is empty or not
    if (! v1.empty()) {
        std::cout << "Vector is not empty" << std::endl;
    } else {
        std::cout << "Vector is empty" << std::endl;
    }

    // Shrinks the vector
    v1.shrink_to_fit();
    std::cout << "Vector elements are : " << std::endl;
    
    /*for (auto it = v1.begin(); it != v1.end(); it++) {
        std::cout << *it << " " << std::endl;
    }*/

    /*auto print = [](const int& n) { 
        std::cout << n << std::endl; 
    };

    std::for_each(v1.begin(), v1.end(), print);*/

    for(auto it : v1) {
        std::cout << it << std::endl; 
    }

    return 0;
}
