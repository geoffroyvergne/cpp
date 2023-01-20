#include <iostream>
#include <cpr/cpr.h>

int main(void) {
    cpr::Response r = cpr::Get(cpr::Url{"https://github.com"});

    std::cout << r.status_code << std::endl;

    return 0;
}
