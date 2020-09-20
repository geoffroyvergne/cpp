#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace client {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    template <typename Iterator>
    bool parse_numbers(Iterator first, Iterator last, double& n){
        using qi::double_;
        using qi::phrase_parse;
        using ascii::space;

        bool r = phrase_parse(first, last, 

            //  Begin grammar
            double_ >> *(',' >> double_),
            //  End grammar

            space);

        if(first != last) {
            return false;
        }

        return r;
    };
}

int main() {
    std::cout << "A comma separated list parser for Spirit..." << std::endl;
    std::cout << "Give me a comma separated list of numbers." << std::endl;
    std::cout << "Type [q or Q] to quit" << std::endl;

    std::string str;
    while(getline(std::cin, str)) {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        if (client::parse_numbers(str.begin(), str.end())) {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << str << " Parses OK: " << std::endl;
            std::cout << "-------------------------\n";
        } else {
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "-------------------------\n";
        }   
    }

    std::cout << "Bye" << std::endl;;
    return 0;
}
