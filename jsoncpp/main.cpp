#include "json/json.h"
#include <iostream>

int main() {
    Json::Value data;
    //Json::Value value;

    data["code"] = 200;
    data["value"] = "Response OK";

    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, data);
    std::cout << json_file << std::endl;

    return 0;
}

