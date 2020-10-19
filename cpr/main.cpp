
#include <iostream>
#include <cpr/cpr.h>

int main(int argc, char** argv) {
    cpr::Response r = cpr::Get(cpr::Url{"https://www.google.fr/"});
                      //cpr::Authentication{"user", "pass"},
                      //cpr::Parameters{{"anon", "true"}, {"key", "value"}});
    //r.status_code;                  // 200
    //r.header["content-type"];       // application/json; charset=utf-8
    //r.text;                         // JSON text string

    std::cout << "status_code : " << r.status_code << std::endl; 
    std::cout << "content-type : " << r.header["content-type"] << std::endl; 
    std::cout << "text : " << r.text << std::endl; 
}
