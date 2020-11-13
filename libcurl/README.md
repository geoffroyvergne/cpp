# libcurl

https://github.com/curl/curl/tree/master/docs/examples

https://curl.haxx.se/libcurl/c/simple.html
https://github.com/curl/curl/blob/master/docs/examples/simple.c

https://github.com/curl/curl/blob/master/docs/examples/parseurl.c


g++ main.cpp -o bin/url-get-test `curl-config --cflags --libs` && bin/url-get-test

g++ main.cpp -o main `curl-config --static-libs` -pthread -static

g++ main.cpp -o main -lcurl   
g++ main.cpp -o main -lcurl -static

g++ main.cpp -o main -lcurl -static `curl-config --static-libs`

cd <project/root>
cmake -S . -B build/
cmake --build build/

g++ -static -o main main.cpp `pkg-config --static --cflags libcurl` `pkg-config --static --libs libcurl`


https://curl.haxx.se/libcurl/c/htmltidy.html
https://raw.githubusercontent.com/curl/curl/master/docs/examples/htmltidy.c

