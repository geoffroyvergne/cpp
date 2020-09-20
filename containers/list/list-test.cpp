#include <iostream>
#include <list>
#include <iterator>

// function for printing the elements in a list
void showList(std::list <int> g) {
    std::list <int> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it) {
        std::cout << "\t" << *it;
    }

    std::cout << "" << std::endl;

}

int main() {
    std::list <int> gqlist1, gqlist2;

    for(int i = 0; i<10; i++) {
        gqlist1.push_back(i * 2);
        gqlist2.push_back(i * 3);
    }
    std::cout << "List 1 (gqlist1) is : " << std::endl;
    showList(gqlist1);

    std::cout << "List 2 (gqlist2) is : " << std::endl;
    showList(gqlist2);

    std::cout << "gqlist1.front() : " << gqlist1.front() << std::endl;
    std::cout << "gqlist1.back() : " << gqlist1.back() << std::endl;

    std::cout << "gqlist1.pop_front() : " << std::endl;
    gqlist1.pop_front();
    showList(gqlist1);

    std::cout << "gqlist2.pop_back() : " << std::endl;
    gqlist2.pop_back();
    showList(gqlist2);

    std::cout << "gqlist1.reverse() : " << std::endl;
    gqlist1.reverse();
    showList(gqlist1);

    std::cout << "gqlist2.sort() : " << std::endl;
    gqlist2.sort();
    showList(gqlist2);

    return 0;
}
