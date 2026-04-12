#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>

#include <yaml-cpp/yaml.h>

#include "config.hxx"
#include "math.hxx"
#include "simulator.hxx"
#include "statistics_collector.hxx"


using edgas::sqr;

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

    edgas::Model model(*config);
    edgas::Simulator simulator(model);
    std::cout << "simulator initialized successfully" << std::endl;

    edgas::SnapshotWriter snapshotWriter("snapshot.txt");
    snapshotWriter.writeSnapshot(model);

    while (true) {
        std::cout << "enter number of steps to simulate (or 0 to quit): ";
        int steps = 0;
        std::cin >> steps;
        if (steps <= 0) {
            break;
        }

        for (int i = 0; i < steps; i++) {
            simulator.step();
        }
        snapshotWriter.writeSnapshot(model);

        double total_energy = 0.0;
        for (const auto& particle : model.particles) {
            total_energy += 0.5 * particle.mass * (sqr(particle.vx) + sqr(particle.vy));
        }
        std::cout << "total energy: " << total_energy << std::endl;

        const auto& stats = simulator.getStatistics();
        std::cout << "total events: " << stats.getTotalEvents() << std::endl;
        std::cout << " - particle collisions: " << stats.totalParticleCollisions << std::endl;
        std::cout << "    - invalid collisions: " << stats.invalidParticleCollisions << std::endl;
        std::cout << " - wall collisions: " << stats.totalWallCollisions << std::endl;
        std::cout << "    - left wall: " << stats.leftWallCollisions << std::endl;
        std::cout << "    - right wall: " << stats.rightWallCollisions << std::endl;
        std::cout << "    - top wall: " << stats.topWallCollisions << std::endl;
        std::cout << "    - bottom wall: " << stats.bottomWallCollisions << std::endl;

    }
    std::cout << "simulation completed successfully" << std::endl;

    return 0;
}

// EOF
