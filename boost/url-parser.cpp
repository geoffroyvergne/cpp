//https://stackoverflow.com/questions/2616011/easy-way-to-parse-a-url-in-c-cross-platform/2616633

#include <iostream>
#include <string>
#include <boost/regex.hpp>

void parse_url(const std::string& url) {
    std::string regex = "(http|https)://([^/ :]+):?([^/ ]*)(/?[^ #?]*)\\x3f?([^ #]*)#?([^ ]*)";

    boost::regex ex(regex);
    boost::cmatch what;

    if(regex_match(url.c_str(), what, ex)) {
        std::string protocol = std::string(what[1].first, what[1].second);
        std::string domain   = std::string(what[2].first, what[2].second);
        std::string port     = std::string(what[3].first, what[3].second);
        std::string path     = std::string(what[4].first, what[4].second);
        std::string query    = std::string(what[5].first, what[5].second);
        std::string fragment = std::string(what[6].first, what[6].second);

        std::cout << "[" << url << "]" << std::endl;
        std::cout << "protocol : " << protocol << std::endl;
        std::cout << "domain : " << domain << std::endl;
        std::cout << "port : " << port << std::endl;
        std::cout << "path : " << path << std::endl;
        std::cout << "query : " << query << std::endl;
        std::cout << "fragment : " << fragment << std::endl;

        std::cout << "-------------------------------" << std::endl;
    }
}

int main(int argc, char** argv) {
    parse_url("http://www.google.com/");
    parse_url("https://mail.google.com/mail/");
    parse_url("https://www.google.com:443/webhp?gws_rd=ssl");
    parse_url("https://www.google.com:443/webhp#testfragment");

    return EXIT_SUCCESS;
}
