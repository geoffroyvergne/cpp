#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace client {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;

    ///////////////////////////////////////////////////////////////////////////
    //  Our number list compiler
    ///////////////////////////////////////////////////////////////////////////
    //[tutorial_numlist4
    template <typename Iterator>
    bool parse_numbers(Iterator first, Iterator last, std::vector<double>& v) {
        using qi::double_;
        using qi::phrase_parse;
        using qi::_1;
        using ascii::space;
        using phoenix::push_back;

        bool r = phrase_parse(first, last,

            //  Begin grammar
            (             
                //double_[push_back(phoenix::ref(v), _1)] >> *(',' >> double_[push_back(phoenix::ref(v), _1)])   
                double_[push_back(phoenix::ref(v), _1)] % ','
                //double_ % ','            
            )
            ,
            //  End grammar

            space);
            //space, v);

        if (first != last) // fail if we did not get a full match
            return false;
        return r;
    }
    //]
}

int main() {
    std::cout << "A comma separated list parser for Spirit" << std::endl;

    std::cout << "Give me a comma separated list of numbers." << std::endl;
    std::cout << "The numbers will be inserted in a vector of numbers" << std::endl;
    std::cout << "Type [q or Q] to quit" << std::endl;

    std::string str;
    while (getline(std::cin, str)) {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        std::vector<double> v;
        if (client::parse_numbers(str.begin(), str.end(), v)) {
            std::cout << "-------------------------" << std::endl;
            std::cout << "Parsing succeeded" << std::endl;
            std::cout << str << " Parses OK: " << std::endl;

            for (std::vector<double>::size_type i = 0; i < v.size(); ++i)
                std::cout << i << ": " << v[i] << std::endl;

            std::cout << "\n-------------------------\n";
        } else {
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "-------------------------\n";
        }
    }

    std::cout << "Bye" << std::endl;
    return 0;
}
