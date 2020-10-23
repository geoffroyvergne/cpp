# ASIO Boost

https://www.boost.org/doc/libs/1_50_0/doc/html/boost_asio/example/http/client/sync_client.cpp

g++ -o bin/sync_client sync_client.cpp -std=c++14 -lboost_system -lpthread

g++ -std=c++11 -o bin/http-client-ssl http-client-ssl.cpp

clang++ -o bin/http-client-ssl -Os -std=c++11 -Wall -pthread http-client-ssl.cpp -lboost_system -lssl -lcrypto