#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>

#include "cpprest/http_listener.h"

#define uclog std::clog

using namespace std;
using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;

void handleGet(const http_request& request) {
    auto path = uri::split_path(uri::decode(request.relative_uri().path()));
    //https://www.nuomiphp.com/eplan/en/13852.html

    json::value result;
	result[U("status")] = json::value::string(U("Hello world!"));

    http_response response(status_codes::OK);
    response.headers().set_content_type(U("application/json"));
    response.set_body(result); 
    
    request.reply(response);
}

void listen(std::string url) {
    http_listener_config listen_config;     
    listen_config.set_timeout(utility::seconds(10));

    http_listener *listener;
    listener = new http_listener(U(url));
    listener->support(methods::GET, handleGet);

    try {
        listener->
            open()
            .then([&listener](){})
            .wait();

        while (true);
    } catch (exception const & e) {
        uclog << e.what() << endl;
        return;
    }

    uclog << U("Waiting for incoming connection...") << endl;

	// Nothing left to do but commit suicide.
	//uclog << U("Terminating JSON listener.") << endl;
	//listener->close();
}

int main() {
    
    listen("http://0.0.0.0:3000/");
	return EXIT_SUCCESS;
}
