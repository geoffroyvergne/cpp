# Docker helloworld

docker build -f Dockerfile -t helloworld .

docker run --rm --name helloworld

run -ti --rm helloworld sh

docker run -ti --rm conanio/clang9-x86 bash