#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <iostream>

int main() {
    boost::system::error_code ec;
    using namespace boost::asio;

    // what we need
    io_service svc;
    //ssl::context ctx(svc, ssl::context::method::sslv23_client);
    //ssl::stream<ip::tcp::socket> ssock(svc, ctx);

    ssl::context ctx(ssl::context::sslv23);
    ctx.set_default_verify_paths();
    
    ip::tcp::resolver resolver(svc);
    auto it = resolver.resolve({"127.0.0.1", "8087"}); // http://localhost:8087 for test
    boost::asio::connect(ssock.lowest_layer(), it);

    ssock.handshake(ssl::stream_base::handshake_type::client);

    // send request
    std::string request("GET /json.response HTTP/1.1\r\n\r\n");
    boost::asio::write(ssock, buffer(request));

    // read response
    std::string response;
    
    do {
        char buf[1024];
        size_t bytes_transferred = ssock.read_some(buffer(buf), ec);
        if (!ec) response.append(buf, buf + bytes_transferred);
    } while (!ec);

    // print and exit
    std::cout << "Response received: '" << response << "'\n";
}