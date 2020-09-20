#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

std::string read_(boost::asio::ip::tcp::socket & socket) {
    boost::asio::streambuf buf;
    boost::asio::read_until( socket, buf, "\n" );
    std::string data = boost::asio::buffer_cast<const char*>(buf.data());

    return data;
}

void send_(boost::asio::ip::tcp::socket & socket, const std::string& message) {
    const std::string msg = message + "\n";
    boost::system::error_code ignored_error;
    boost::asio::write( socket, boost::asio::buffer(message), ignored_error);
}

int main() {
  try {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8888));
    boost::asio::ip::tcp::socket socket(io_context);
    acceptor.accept(socket);

    for (;;) {
        std::string recieved_message = read_(socket);
        std::cout << "Message : " << recieved_message << std::endl;

        std::string send_message = "Message recieved!\n";
        send_(socket, send_message);
    }
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
