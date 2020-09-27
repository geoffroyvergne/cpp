# VCPKG

https://cpphub.org/libraries

brew install vcpkg

vcpkg with CMake
-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake

[path to vcpkg]
/usr/local/Cellar/vcpkg/2020.07/libexec/scripts/buildsystems/vcpkg.cmake


-DCMAKE_TOOLCHAIN_FILE=/usr/local/Cellar/vcpkg/2020.07/libexec/scripts/buildsystems/vcpkg.cmake


settings.json
{
  "cmake.configureSettings": {
    "CMAKE_TOOLCHAIN_FILE": "[vcpkg root]/scripts/buildsystems/vcpkg.cmake"
  }
}

With CMake, you will still need to find_package

