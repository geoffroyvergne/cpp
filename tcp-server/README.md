# TCP Server

lsof -i -P | grep 8888 

https://codereview.stackexchange.com/questions/194602/basic-multithread-server-code

https://github.com/AnkitDimri/multithread-tcp-server/blob/master/server.cpp

https://www.codeproject.com/Articles/1264257/Socket-Programming-in-Cplusplus-using-boost-asio-T

# boost.asio
https://www.boost.org/doc/libs/1_73_0/doc/html/boost_asio.html
https://www.boost.org/doc/libs/1_73_0/doc/html/boost_asio/tutorial/tutdaytime3.html
https://www.boost.org/doc/libs/1_73_0/doc/html/boost_asio/tutorial.html

g++ ascync-tcp-server.c -o bin/ascync-tcp-server -std=c++14 -Wall -Wextra -lboost_system -lpthread