#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

int main(int argc, char** argv) {
    try {

        boost::property_tree::ptree pt;
        boost::property_tree::ini_parser::read_ini("config.ini", pt);
        
        std::cout << "Section1.Value1 : " << pt.get<std::string>("Section1.Value1") << std::endl;
        std::cout << "Section1.Value2 : " << pt.get<std::string>("Section1.Value2") << std::endl;

    } catch(std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
        return 1;
    } catch(...) {
        std::cerr << "Exception of unknown type!" << std::endl;
    }

    return EXIT_SUCCESS;
}