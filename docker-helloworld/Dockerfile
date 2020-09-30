# ------------- BUILD ----------------

FROM conanio/clang9-x86 as build

COPY src/ .
#WORKDIR /usr/src/app

#RUN clang++ -static -o helloworld hello-world.cpp
RUN clang++ -o helloworld hello-world.cpp

RUN ./helloworld

# ------------- RUN ----------------

#FROM ubuntu
FROM gcr.io/distroless/cc

#RUN apt-get update && apt-get install -y libc6++

COPY --from=build /home/conan/helloworld /helloworld
CMD ["/helloworld"]
