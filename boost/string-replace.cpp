#include <iostream>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>


int main() {
    std::string testspace1 = "test   \r\nspace\n \t 1";
    std::cout << "testspace1 : " << testspace1 << std::endl;

    boost::algorithm::replace_all(testspace1, " ", "");
    boost::algorithm::replace_all(testspace1, "\r\n", "");
    boost::algorithm::replace_all(testspace1, "\r", "");
    boost::algorithm::replace_all(testspace1, "\n", "");
    boost::algorithm::replace_all(testspace1, "\t", "");

    std::cout << "testspace1 : " << testspace1 << std::endl;

}