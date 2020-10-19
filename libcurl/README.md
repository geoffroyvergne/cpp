# libcurl

https://github.com/curl/curl/tree/master/docs/examples

https://curl.haxx.se/libcurl/c/simple.html
https://github.com/curl/curl/blob/master/docs/examples/simple.c

https://github.com/curl/curl/blob/master/docs/examples/parseurl.c


g++ main.cpp -o bin/url-get-test `curl-config --cflags --libs` && bin/url-get-test

g++ main.cpp -o main `curl-config --static-libs` -pthread -static

cd <project/root>
cmake -S . -B build/
cmake --build build/