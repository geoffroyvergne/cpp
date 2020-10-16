#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

#include "tutorialConfig.h"

#ifdef USE_MYMATH
#  include "mysqrt.h"
#endif

int main(int argc, char* argv[])
{
  if (argc < 2) {
    std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "."
              << Tutorial_VERSION_MINOR << std::endl;
    std::cout << "Usage: " << argv[0] << " number" << std::endl;
    return 1;
  }

  // convert input to double
  const double inputValue = atof(argv[1]);

  // calculate square root
  //const double outputValue = sqrt(inputValue);

  //std::cout << USE_MYMATH << std:endl;

  #ifdef USE_MYMATH
    const double outputValue = mysqrt(inputValue);
  #else
    const double outputValue = sqrt(inputValue);
  #endif

  std::cout << "The square root of " << inputValue << " is " << outputValue
            << std::endl;
  return 0;
}
