#include <iostream>
#include <vector>

int main() {
    std::vector<int> v1;

    // fill the array with five 10 times
    v1.assign(10, 5);

    std::cout << "The vector elements are : " << std::endl;
    for (int i = 0; i < v1.size(); i++) {
        std::cout << v1[i] << " " << std::endl;
    }

    v1.push_back(15);
    int n = v1.size();
    std::cout << "The last element is : " << v1[n -1] << std::endl;

    // remove last element
    v1.pop_back();

    // print the vector
    std::cout << "The vector elements are : " << std::endl;
    for (int i = 0; i < v1.size(); i++) {
        std::cout << v1[i] << " " << std::endl;
    }

    std::cout << "The first element is: " << v1[0] << std::endl;

    // remove the first element
    v1.erase(v1.begin());

    std::cout << "The first element is: " << v1[0] << std::endl; 

    // insert at the beginning
    v1.emplace(v1.begin(), 5);
    std::cout << "The first element is: " << v1[0] << std::endl;

    // insert 20 at the end
    v1.emplace_back(20);
    n = v1.size();
    std::cout << "Vector size after erase() : " << v1.size() << std::endl;

    // two vectors to perform swap
    std::vector<int> v2, v3;
    v2.push_back(1);
    v2.push_back(2);
    v3.push_back(3);
    v3.push_back(4);

    std::cout << "Vector 2 : " << std::endl;
    for (int i = 0; i < v2.size(); i++) {
        std::cout << v2[i] << " " << std::endl;
    }

    std::cout << "Vector 3 : " << std::endl;
    for (int i = 0; i < v3.size(); i++) {
        std::cout << v3[i] << " " << std::endl;
    }

    // swap v2 and v3
    v2.swap(v3);

    std::cout << "After swap Vector 2 : " << std::endl;
    for (int i = 0; i < v2.size(); i++) {
        std::cout << v2[i] << " " << std::endl;
    }

    std::cout << "After swap Vector 3 : " << std::endl;
    for (int i = 0; i < v3.size(); i++) {
        std::cout << v3[i] << " " << std::endl;
    }

    return 0;
}
