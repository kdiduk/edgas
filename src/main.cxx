#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>

#include <yaml-cpp/yaml.h>

#include "config.hxx"
#include "simulator.hxx"
#include "statistics_collector.hxx"


int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

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

    edgas::Simulator simulator(*config);
    for (int i = 0; i < 100; ++i) {
        simulator.step();
    }
    std::cout << "simulation completed successfully" << std::endl;

    const auto& stats = simulator.getStatistics();
    std::cout << "total particle collisions: " << stats.totalParticleCollisions << std::endl;
    std::cout << "total invalid collisions: " << stats.invalidParticleCollisions << std::endl;
    std::cout << "total wall collisions: " << stats.totalWallCollisions << std::endl;
    std::cout << "  left wall collisions: " << stats.leftWallCollisions << std::endl;
    std::cout << "  right wall collisions: " << stats.rightWallCollisions << std::endl;
    std::cout << "  top wall collisions: " << stats.topWallCollisions << std::endl;
    std::cout << "  bottom wall collisions: " << stats.bottomWallCollisions << std::endl;
    
    return 0;
}

// EOF
