#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

int main() {
    const std::string filename = "config.xml";

    // Create an empty property tree object
    //using boost::property_tree::ptree;
    //ptree pt;
    namespace pt = boost::property_tree;
    pt::ptree root;

    read_xml(filename, root);

    for(const ptree::value_type &v : root)
    {
        std::cout << v.first << std::endl;
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}