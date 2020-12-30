#include <iostream>
#include <httplib.h>

int main() {
    httplib::Server svr;

    svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.listen("127.0.0.1", 8080);
}
