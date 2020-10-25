# https client

# Compiling 

g++ -c -o SSLClient.o SSLClient.cpp 
g++ -o SSLClient SSLClient.o -lssl -lcrypto 

clang++ -o bin/httpsclient main.cpp -lssl -lcrypto 