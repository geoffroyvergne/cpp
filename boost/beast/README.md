# Boost beast http client

https://www.boost.org/doc/libs/1_74_0/libs/beast/example/http/client/sync/http_client_sync.cpp

ln -s /usr/local/opt/openssl/include/openssl /usr/local/include

-lssl -lcrypto


g++ -Wall -std=c++11 -o bin/http_client_sync http_client_sync.cpp


g++ -Wall -std=c++11 -o bin/http_client_sync-ssl http_client_sync-ssl.cpp -lssl -lcrypto