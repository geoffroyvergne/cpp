#include <iostream>
#include <iterator>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

int main(int argc, char** argv) {
    try {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "produce help message")
            ("version,v", "get version")
            ("compression,c", po::value<double>(), "set compression level")
        ;

        po::variables_map vm;        
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return EXIT_SUCCESS;
        }

        if (vm.count("version")) {
            std::cout << "V 1.0" << "\n";
            return EXIT_SUCCESS;
        }

        if (vm.count("compression")) {
            std::cout << "Compression level was set to " << vm["compression"].as<double>() << std::endl;
        }

    } catch(std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
        return 1;
    } catch(...) {
        std::cerr << "Exception of unknown type!" << std::endl;
    }

    return EXIT_SUCCESS;
}