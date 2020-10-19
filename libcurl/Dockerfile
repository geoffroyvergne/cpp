FROM conanio/clang9 AS build

RUN sudo apt-get update && sudo apt-get install -f libcurl4-openssl-dev

COPY main.cpp .

RUN g++ main.cpp -o main `curl-config --static-libs` -pthread -static

