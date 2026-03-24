#include <filesystem>
#include <iostream>
#include <string>

#include <yaml-cpp/yaml.h>

#include "config.hxx"


int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "missing config file name argument" << std::endl;
        return 1;
    }

    auto config = edgas::Config::from_file(argv[1]);
    if (!config) {
        std::cout << "failed to load config" << std::endl;
        return 1;
    }

    std::cout << "config loaded successfully:" << std::endl;
    std::cout << "  particle count: " << config->particleCount << std::endl;
    std::cout << "  particle radius: " << config->particleRadius << std::endl;
    std::cout << "  particle mass: " << config->particleMass << std::endl;
    std::cout << "  dimension x: " << config->dimensionX << std::endl;
    std::cout << "  dimension y: " << config->dimensionY << std::endl;
    
    return 0;
}

// EOF
