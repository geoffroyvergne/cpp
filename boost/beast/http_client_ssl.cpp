#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <cstdlib>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;
namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
namespace ssl = net::ssl;       // from <boost/asio/ssl.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

int main() {

        auto const protocol = "https";
        auto const host = "www.google.fr";
        auto const port = "443";
        auto const target = "/";
        int version = 11;

    try {
        net::io_context ioc;

        // Create a context that uses the default paths for finding CA certificates.
        ssl::context ctx(ssl::context::sslv23);
        ctx.set_default_verify_paths();

        // Open a socket and connect it to the remote host.
        boost::asio::io_context io_context;
        ssl_socket sock(io_context, ctx);
        tcp::resolver resolver(io_context);
        tcp::resolver::query query(host, protocol);
        boost::asio::connect(sock.lowest_layer(), resolver.resolve(query));
        sock.lowest_layer().set_option(tcp::no_delay(true));

        // Perform SSL handshake and verify the remote host's certificate.
        //sock.set_verify_mode(ssl::verify_peer);
        sock.set_verify_mode(ssl::verify_none);
        sock.set_verify_callback(ssl::host_name_verification(host));
        sock.handshake(ssl_socket::client);

        // These objects perform our I/O
        
        //tcp::resolver resolver(ioc);
        beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

        if(! SSL_set_tlsext_host_name(stream.native_handle(), host))
        {
            beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
            throw beast::system_error{ec};
        }

        // Look up the domain name
        auto const results = resolver.resolve(host, port);

        // Make the connection on the IP address we get from a lookup
        beast::get_lowest_layer(stream).connect(results);

        // Perform the SSL handshake
        stream.handshake(ssl::stream_base::client);

        // Set up an HTTP GET request message
        http::request<http::string_body> req{http::verb::get, target, version};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // Send the HTTP request to the remote host
        http::write(stream, req);

        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;

        // Declare a container to hold the response
        http::response<http::dynamic_body> res;

        // Receive the HTTP response
        http::read(stream, buffer, res);

        // Write the message to standard out
        std::string body = boost::beast::buffers_to_string(res.body().data());
        std::cout << "Body : " << body.length() << std::endl;
        std::cout << "Reason : " << res.reason() << std::endl;

        // Gracefully close the stream
        beast::error_code ec;
        stream.shutdown(ec);
        /*if(ec == net::error::eof)
        {
            // Rationale:
            // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
            ec = {};
        }
        if(ec)
            throw beast::system_error{ec};*/

        // If we get here then the connection is closed gracefully

    } catch(std::exception const& e) {
        
        std::cerr << "Http Client Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}