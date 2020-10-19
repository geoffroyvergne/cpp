#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_string(boost::asio::streambuf& streambuf) {
    return {
        boost::asio::buffers_begin(streambuf.data()), 
        boost::asio::buffers_end(streambuf.data())
    };
}

/*std::vector<std::string> extractHeader(std::string header) {
    std::vector<std::string> results;
        boost::split(results, header, boost::is_any_of(":"));
        //std::string key = results.at(0);
        //std::string value = results.at(1);

        //headerMap.insert(std::pair<std::string,std::string>(resutls.begin(), results.end()));
        boost::trim(results.at(0));
        boost::algorithm::to_lower(results.at(0));
        boost::trim(results.at(1));
        boost::algorithm::to_lower(results.at(1));
}*/

int main(int argc, char* argv[]) {

    std::cout << "boost asio http client " << std::endl;

    try {

        /*if (argc != 3) {
            std::cout << "Usage: sync_client <server> <path>\n";
            std::cout << "Example:\n";
            std::cout << "  sync_client www.boost.org /LICENSE_1_0.txt\n";
            return 1;
        }*/

        /*
            argv[0] sync_client
            argv[1] www.boost.org
            argv[2] /LICENSE_1_0.txt
        */

        std::string scheme = "http";
        std::string host = "www.google.fr";
        std::string path = "/";

        std::string content;
        unsigned int statusCode;
        //std::vector <std::string> headerList;
        std::string httpVersion;

        boost::asio::io_service io_service;

        // Get a list of endpoints corresponding to the server name.
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(host,scheme);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        // Try each endpoint until we successfully establish a connection.
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        boost::asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "GET " << path << " HTTP/1.0\r\n";
        request_stream << "Host: " << host << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";

        // Send the request.
        boost::asio::write(socket, request);

        // Read the response status line. The response streambuf will automatically
        // grow to accommodate the entire line. The growth may be limited by passing
        // a maximum size to the streambuf constructor.
        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");

        // Check that response is OK.
        std::istream response_stream(&response);
        
        response_stream >> httpVersion;
        
        response_stream >> statusCode;
        std::string status_message;
        std::getline(response_stream, status_message);

        if (!response_stream || httpVersion.substr(0, 5) != "HTTP/") {
            std::cout << "Invalid response\n";
            exit(EXIT_FAILURE);
        }  

        //std::string test;
        //response_stream >> test;    
        //std::cout << "test : " << test << std::endl;          

        // Read the response headers, which are terminated by a blank line.
        boost::asio::read_until(socket, response, "\r\n\r\n");

        // Process the response headers.

        //std::map<std::string, std::string> headerMap = getHeaders(response_stream);
        
        std::map<std::string, std::string> headerMap;
        std::string header;
        while (std::getline(response_stream, header) && header != "\r") {
            //std::cout << header << "\n";
            //headerList.push_back(header);

            std::vector<std::string> results;
            boost::split(results, header, boost::is_any_of(":"));
            //std::string key = results.at(0);
            //std::string value = results.at(1);

            //headerMap.insert(std::pair<std::string,std::string>(resutls.begin(), results.end()));
            boost::trim(results.at(0));
            boost::algorithm::to_lower(results.at(0));
            boost::trim(results.at(1));
            boost::algorithm::to_lower(results.at(1));

            headerMap[results.at(0)] = results.at(1);
            //headerMap["key1"] = "val1";
        }

        //std::string tempContent;
        // Write whatever content we already have to output.
        if (response.size() > 0) {            
            content.append(make_string(response));
        }

        // Read until EOF, writing data to output as we go.
        boost::system::error_code error;
        while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error)) {            
            content.append(make_string(response));
        }

        if (error != boost::asio::error::eof) {
            throw boost::system::system_error(error);
        }

        std::cout << content << std::endl;
        std::cout << content.size() << std::endl;
        std::cout << statusCode << std::endl;       
        std::cout << httpVersion << std::endl;

        //std::string contentType = headerMap.at("Content-Type");
        std::cout << "content-type : " << headerMap.at("content-type") << std::endl;

        std::cout << "Headers : " << std::endl;
        /*for (std::string header: headerList) {
            std::cout << header << std::endl;
        }*/

    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }

    return EXIT_SUCCESS;
}
