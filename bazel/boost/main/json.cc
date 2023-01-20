#include <iostream>
#include <boost/json.hpp>

int main() {
  auto jv = boost::json::parse(R"({"hello": "world"})");

  std::cout << jv.as_object().at("hello") << std::endl;

  return 0;
}
