#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>

class TcpConnection: public boost::enable_shared_from_this<TcpConnection> {
    public: typedef boost::shared_ptr<TcpConnection> pointer;

    static pointer create(boost::asio::io_context& io_context) {
        return pointer(new TcpConnection(io_context));
    }

    void send_(boost::asio::ip::tcp::socket & socket, const std::string& message) {
        boost::asio::async_write(socket_, boost::asio::buffer(message),
        boost::bind(&TcpConnection::handle_write, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
    }

    std::string read_(boost::asio::ip::tcp::socket & socket) {
        boost::asio::streambuf buf;
        boost::asio::read_until(socket_, buf, "\n" );
        std::string data = boost::asio::buffer_cast<const char*>(buf.data());

        return data;
    }

    boost::asio::ip::tcp::socket& socket() {
        return socket_;
    }

    void start() {
        for(;;) {
            std::string recieved_message = read_(socket());   
            boost::algorithm::trim(recieved_message);         

            if(recieved_message.empty()) continue;

            std::cout << "Message : " << recieved_message << std::endl;

            std::string send_message = "Message recieved!\n";
            send_(socket_, send_message);
        }
    }

    private: TcpConnection(boost::asio::io_context& io_context): socket_(io_context) {}

    void handle_write(const boost::system::error_code&, size_t) {}

    boost::asio::ip::tcp::socket socket_;
    //std::string message_;
};

class TcpServer {
    public: TcpServer(boost::asio::io_context& io_context) : io_context_(io_context), acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8888)) {
        start_accept();
    }

    public: TcpServer(boost::asio::io_context& io_context, boost::asio::ip::tcp ip_version, int port) : io_context_(io_context), acceptor_(io_context, boost::asio::ip::tcp::endpoint(ip_version, port)) {
        start_accept();
    }

    private: void start_accept() {
        TcpConnection::pointer new_connection = TcpConnection::create(io_context_);

        acceptor_.async_accept(new_connection->socket(),
        boost::bind(&TcpServer::handle_accept, this, new_connection,
        boost::asio::placeholders::error));
    }

    void handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error) {
        if (!error) {
            new_connection->start();
        }

        start_accept();
    }

    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
};

int main() {
  try {
    boost::asio::io_context io_context;
    TcpServer TcpServer(io_context, boost::asio::ip::tcp::v4(), 8888);
    io_context.run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
