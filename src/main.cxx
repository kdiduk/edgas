#include <filesystem>
#include <iostream>
#include <string>

#include <yaml-cpp/yaml.h>


int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "missing config file name argument" << std::endl;
        return 1;
    }

    auto fileName = std::string(argv[1]);
    if (!std::filesystem::exists(fileName)) {
        std::cout << fileName << " does not exist" << std::endl;
        return 1;
    }

    YAML::Node configFileNode;
    try {
        configFileNode = YAML::LoadFile(fileName);
    }
    catch (const YAML::BadFile& ex) {
        std::cout << "failed to load config file " << fileName << ": " << ex.what() << std::endl;
        return 1;
    }

    std::cout << "config file " << fileName << " loaded successfully" << std::endl;

    YAML::Node particlesNode = configFileNode["particles"];
    if (!particlesNode) {
        std::cout << "missing particles node in config file " << fileName << std::endl;
        return 1;
    }

    if (auto&& countNode = particlesNode["count"]) {
        std::cout << "particles count: " << countNode.as<int>() << std::endl;
    }
    else {
        std::cout << "missing particles count in config file " << fileName << std::endl;
    }

    if (auto&& radiusNode = particlesNode["radius"]) {
        std::cout << "particles radius: " << radiusNode.as<double>() << std::endl;
    }
    else {
        std::cout << "missing particles radius in config file " << fileName << std::endl;
    }

    std::cout << "Hello, World!" << std::endl;

    return 0;
}

// EOF
