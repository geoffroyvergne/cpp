# Boost beast http client

## Client
https://www.boost.org/doc/libs/1_74_0/libs/beast/example/http/client/sync/http_client_sync.cpp
https://aticleworld.com/ssl-server-client-using-openssl-in-c/

g++ -Wall -std=c++11 -o bin/http_client_sync http_client_sync.cpp

## Client SSL
https://www.boost.org/doc/libs/1_74_0/libs/beast/example/http/client/sync-ssl/http_client_sync_ssl.cpp
https://www.boost.org/doc/libs/1_74_0/libs/beast/example/common/root_certificates.hpp

g++ -Wall -std=c++11 -o bin/http_client_sync-ssl http_client_sync-ssl.cpp -lssl -lcrypto

clang++ -o bin/http_client_sync-ssl -Os -std=c++11 -Wall -pthread http_client_sync-ssl.cpp -lboost_system -lssl -lcrypto

clang++ -std=c++11 -O3 http_client_sync-ssl.cpp -o bin/http_client_sync-ssl \
          -I/usr/local/opt/openssl/include/ \
          -L/usr/local/opt/openssl/lib/ -lssl -lcrypto
# cpp boost bease

https://www.boost.org/doc/libs/1_74_0/libs/beast/doc/html/beast/examples.html
https://github.com/boostorg/beast/blob/develop/example/http/client/sync-ssl/http_client_sync_ssl.cpp


ln -s /usr/local/opt/openssl/include/openssl /usr/local/include
-lssl -lcrypto

## Server
g++ -Wall -std=c++11 -o bin/http_server_sync http_server_sync.cpp
./bin/http_server_sync
curl localhost:3000/html/test.html

## REST API

g++ -Wall -std=c++11 -o bin/rest_api_sync rest_api_sync.cpp
./bin/rest_api_sync
curl localhost:3000/html/test.html

## http client ssl

g++ -Wall -std=c++11 -o bin/http_client_sync-ssl http_client_sync-ssl.cpp

clang++ -std=c++11 -O3 http_client_sync-ssl.cpp -o bin/http_client_sync-ssl \
          -I/usr/local/Cellar/openssl@1.1/1.1.1h/include \
          -L /usr/local/Cellar/openssl@1.1/1.1.1h/lib -lssl -lcrypto