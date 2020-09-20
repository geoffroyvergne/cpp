#include <iostream>
#include <boost/asio.hpp>

//using namespace boost::asio;
//using ip::tcp;
//using std::string;
//using std::cout;
//using std::endl;

std::string read_(boost::asio::ip::tcp::socket & socket) {
    boost::asio::streambuf buf;
    boost::asio::read_until( socket, buf, "\n" );
    std::string data = boost::asio::buffer_cast<const char*>(buf.data());
    return data;
}

void send_(boost::asio::ip::tcp::socket & socket, const std::string& message) {
    const std::string msg = message + "\n";
    boost::asio::write( socket, boost::asio::buffer(message) );
}

int main() {
    boost::asio::io_service io_service;

    //listen for new connection
    boost::asio::ip::tcp::acceptor acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8888 ));
    
    //socket creation 
    boost::asio::ip::tcp::socket socket_(io_service);
    
    //waiting for connection
    acceptor_.accept(socket_);

    for(;;) {
        //read operation
        std::string recieved_message = read_(socket_);
        std::cout << "Message : " << recieved_message << std::endl;
        
        //write operation
        std::string send_message = "Hello From Server!\n";
        send_(socket_, send_message);
        //std::cout << "Servent sent Hello message to Client!" << std::endl;
    }

    return 0;
}
