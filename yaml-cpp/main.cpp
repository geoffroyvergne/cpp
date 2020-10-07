#include <iostream>
#include <fstream>
#include "yaml-cpp/yaml.h"

int main() {
    std::cout << "yaml-cpp" << std::endl;
    //std::ifstream fin("test.yaml");

    YAML::Node root;
    try {
        root = YAML::LoadFile("config.yaml");
    } catch (const std::exception& e){
        std::cout << e.what() << "\n";
        return 0;
    }

    if (root["height"]) {
        std::cout << "Height: " << root["height"].as<int>() << std::endl;
        std::cout << "animals -> cat : " << root["animals"]["cat"].as<std::string>() << std::endl;
    }

    const std::string someComplexPath = root["some"]["complex"]["path"].as<std::string>();
    std::cout << "someComplexPath: " << someComplexPath << std::endl;

    for (YAML::const_iterator it = root.begin(); it != root.end(); ++it){
        std::cout << "First: " << it->first.Type() << " " << it->first.as<std::string>() << "\n";
        //it->second.as<std::string>(); // can't do this until it's type is checked!!

        //YAML::NodeType::Sequence;
        // Undefined, Null, Scalar, Sequence, Map 
    }

    // ------------

    /*YAML::Node lineup = YAML::Load("{1B: Prince Fielder, 2B: Rickie Weeks, LF: Ryan Braun}");
    for(YAML::const_iterator it=lineup.begin();it!=lineup.end();++it) {
        std::cout << "Playing at " << it->first.as<std::string>() << " is " << it->second.as<std::string>() << "\n";
    }

    lineup["RF"] = "Corey Hart";
    lineup["C"] = "Jonathan Lucroy";
    assert(lineup.size() == 5);*/

    // --------------

    /*YAML::Node node = YAML::Load("[1, 2, 3]");
    assert(node.Type() == YAML::NodeType::Sequence);
    assert(node.IsSequence());  // a shortcut!*/

    // ----------------

    /*YAML::Node primes = YAML::Load("[2, 3, 5, 7, 11]");
    for (std::size_t i=0;i<primes.size();i++) {
        std::cout << primes[i].as<int>() << "\n";
    }
    // or:
    for (YAML::const_iterator it=primes.begin();it!=primes.end();++it) {
        std::cout << it->as<int>() << "\n";
    }

    primes.push_back(13);
    assert(primes.size() == 6);*/

}
