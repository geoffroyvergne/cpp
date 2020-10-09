# conan.io

https://conan.io/center/
https://github.com/conan-io/examples
https://docs.conan.io/en/latest/getting_started.html

brew install conan

# Build only missing packages
conan install --build=missing

# Rebuild all packages
conan install --build=force

# remove packages
conan remove -f '*'

# graph of dependencies
conan info . --graph=file.html

# linux gcc recent version
default profil
compiler.libcxx=libstdc++11