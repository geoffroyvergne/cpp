FROM danger89/cmake AS build
#WORKDIR /src
COPY CMakeLists.txt main.cpp ./
#RUN cmake . && make
RUN cmake -DCMAKE_CXX_FLAGS=-static . -B build/ && cmake --build build/

FROM alpine
#WORKDIR /opt/hello-world
COPY --from=build ./build/helloworld ./
CMD ["./helloworld"]
