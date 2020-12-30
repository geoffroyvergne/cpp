#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/config.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

// This function produces an HTTP response for the given
// request. The type of the response object depends on the
// contents of the request, so the interface requires the
// caller to pass a generic lambda for receiving the response.
template<class Body, class Allocator, class Send>
void handle_request(beast::string_view doc_root, http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send) {    
    
    const auto response = 
        [&req](boost::beast::string_view content, boost::beast::string_view contentType, http::status status) {
		http::response<http::string_body> res{ status, req.version() };
		res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
		res.set(http::field::content_type, contentType);
		res.keep_alive(req.keep_alive());
        res.body() = content.to_string();
        res.content_length(content.length());
		res.prepare_payload();
		return res;
	};

    if( req.target().empty() || req.target()[0] != '/' || req.target().find("..") != beast::string_view::npos ) {
        //return send(bad_request("Illegal request-target"));
        //std::cout << "Illegal request-target" << std::endl;

        return send(response("400 bad request", "application/text", http::status::bad_request)); 
    }

    // GET /test
    if(req.target() == "/test" && req.method() == http::verb::get) {
        std::string content = "GET /test endpoint";
        std::cout << content << std::endl;
        

        return send(response(content, "application/text", http::status::ok));
    }

    return send(response("404 not found", "application/text", http::status::not_found));

}

//------------------------------------------------------------------------------

// Report a failure
void fail(beast::error_code ec, char const* what) {
    std::cerr << what << ": " << ec.message() << "\n";
}

// This is the C++11 equivalent of a generic lambda.
// The function object is used to send an HTTP message.
template<class Stream> struct send_lambda {
    Stream& stream_;
    bool& close_;
    beast::error_code& ec_;

    explicit send_lambda(Stream& stream, bool& close, beast::error_code& ec) : stream_(stream), close_(close), ec_(ec){}

    template<bool isRequest, class Body, class Fields>
    void operator()(http::message<isRequest, Body, Fields>&& msg) const {
        // Determine if we should close the connection after
        close_ = msg.need_eof();

        // We need the serializer here because the serializer requires
        // a non-const file_body, and the message oriented version of
        // http::write only works with const messages.
        http::serializer<isRequest, Body, Fields> sr{msg};
        http::write(stream_, sr, ec_);
    }
};

// Handles an HTTP server connection
void do_session(tcp::socket& socket, std::shared_ptr<std::string const> const& doc_root) {
    bool close = false;
    beast::error_code ec;

    // This buffer is required to persist across reads
    beast::flat_buffer buffer;

    // This lambda is used to send messages
    send_lambda<tcp::socket> lambda{socket, close, ec};

    for(;;) {
        // Read a request
        http::request<http::string_body> req;
        http::read(socket, buffer, req, ec);

        if(ec == http::error::end_of_stream) break;
        if(ec) return fail(ec, "read");

        // Send the response
        handle_request(*doc_root, std::move(req), lambda);
        if(ec) return fail(ec, "write");
        if(close) break;
    }

    // Send a TCP shutdown
    socket.shutdown(tcp::socket::shutdown_send, ec);

    // At this point the connection is closed gracefully
}

//------------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    try {        
        auto const address = net::ip::make_address("0.0.0.0");
        auto const port = static_cast<unsigned short>(3000);
        auto const doc_root = std::make_shared<std::string>("./html");

        // The io_context is required for all I/O
        net::io_context ioc{1};

        // The acceptor receives incoming connections
        tcp::acceptor acceptor{ioc, {address, port}};
        for(;;) {
            // This will receive the new connection
            tcp::socket socket{ioc};

            // Block until we get a connection
            acceptor.accept(socket);

            // Launch the session, transferring ownership of the socket
            std::thread{
                std::bind(&do_session, std::move(socket), doc_root)
            }.detach();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}