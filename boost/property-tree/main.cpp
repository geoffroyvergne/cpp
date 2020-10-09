#include <fstream>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace pt = boost::property_tree;

void readYaml() {
    std::cout << "readYaml" << std::endl;

    pt::ptree root;
    pt::read_json("config.yaml", root);

    /*int height = root.get<int>("height", 0);
    std::string msg = root.get<std::string>("some.complex.path");

    std::cout << "Property height : " << height << std::endl;
    std::cout << "Property some.complex.path : " << msg << std::endl;*/
}

void readJson() {
    std::cout << "readJson" << std::endl;

    pt::ptree root;
    pt::read_json("config.json", root);

    int height = root.get<int>("height", 0);
    std::string msg = root.get<std::string>("some.complex.path");

    std::cout << "Property height : " << height << std::endl;
    std::cout << "Property some.complex.path : " << msg << std::endl;
}

void readXml() {
    std::cout << "readXml" << std::endl;

    pt::ptree root;
    pt::read_xml("config.xml", root);

    int height = root.get<int>("root.height", 0);
    std::string msg = root.get<std::string>("root.some.complex.path");

    std::cout << "Property height : " << height << std::endl;
    std::cout << "Property some.complex.path : " << msg << std::endl;
}

int main() {
    std::cout << "Property tree test" << std::endl;

    readJson();
    readXml();
    readYaml();
}
