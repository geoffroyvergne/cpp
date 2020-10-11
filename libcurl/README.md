# libcurl

https://github.com/curl/curl/tree/master/docs/examples

https://curl.haxx.se/libcurl/c/simple.html
https://github.com/curl/curl/blob/master/docs/examples/simple.c

https://github.com/curl/curl/blob/master/docs/examples/parseurl.c


g++ url-get-test.cpp -o bin/url-get-test `curl-config --cflags --libs` && bin/url-get-test

cd <project/root>
cmake -S . -B build/
cmake --build build/