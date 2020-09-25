#include "gumbo/gumbo.h"
#include <iostream>

int main() {
  std::cout << "test gumbo" << std::endl;
  GumboOutput* output = gumbo_parse("<h1>Hello, World!</h1>");
  // Do stuff with output->root
  gumbo_destroy_output(&kGumboDefaultOptions, output);
}
