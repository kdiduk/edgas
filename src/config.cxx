#include "config.hxx"

#include <filesystem>
#include <iostream>

#include <yaml-cpp/yaml.h>


namespace edgas {

    std::unique_ptr<Config> Config::from_file(const std::string& fileName) {

        if (!std::filesystem::exists(fileName)) {
            std::cerr << fileName << " does not exist" << std::endl;
            return nullptr;
        }

        auto config = std::make_unique<Config>();

        YAML::Node configFileNode;
        try {
            configFileNode = YAML::LoadFile(fileName);
        }
        catch (const YAML::BadFile& ex) {
            std::cerr << "failed to load config file " << fileName << ": " << ex.what() << std::endl;
            return nullptr;
        }

        YAML::Node particlesNode = configFileNode["particles"];
        if (!particlesNode) {
            std::cerr << "missing particles node in config file " << fileName << std::endl;
            return nullptr;
        }

        if (auto&& countNode = particlesNode["count"]) {
            config->particleCount = countNode.as<int>();
        }
        else {
            std::cerr << "missing particles count in config file " << fileName << std::endl;
            return nullptr;
        }

        if (auto&& radiusNode = particlesNode["radius"]) {
            config->particleRadius = radiusNode.as<double>();
        }
        else {
            std::cerr << "missing particles radius in config file " << fileName << std::endl;
            return nullptr;
        }

        YAML::Node dimensionsNode = configFileNode["dimensions"];
        if (!dimensionsNode) {
            std::cerr << "missing dimensions node in config file " << fileName << std::endl;
            return nullptr;
        }

        if (auto&& xDimensionNode = dimensionsNode["x"]) {
            config->dimensionX = xDimensionNode.as<int>();
        }
        else {
            std::cerr << "missing x dimension in config file " << fileName << std::endl;
            return nullptr;
        }

        if (auto&& yDimensionNode = dimensionsNode["y"]) {
            config->dimensionY = yDimensionNode.as<int>();
        }
        else {
            std::cerr << "missing y dimension in config file " << fileName << std::endl;
            return nullptr;
        }

        return config;
    }
}

// EOF