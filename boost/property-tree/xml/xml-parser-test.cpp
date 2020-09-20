#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

int main() {
    const std::string filename = "config.xml";

    // Create an empty property tree object
    using boost::property_tree::ptree;
    ptree pt;

    read_xml(filename, pt);

    for(const ptree::value_type &v : pt)
    {
        std::cout << v.first << std::endl;
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}