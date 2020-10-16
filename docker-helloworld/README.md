# Docker helloworld

docker build -f Dockerfile -t helloworld .

docker run --rm --name helloworld helloworld

docker run -ti helloworld sh

docker run -ti --rm conanio/clang9-x86 bash