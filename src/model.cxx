#include <cassert>
#include <cmath>

#include <algorithm>
#include <numbers>
#include <numeric>
#include <random>

#include "math.hxx"
#include "model.hxx"
#include "config.hxx"


namespace edgas {

    static std::mt19937 gen(std::random_device{}());

    Model::Model(const Config& config)
        :   particles_storage(config.particleCount, Particle(config.particleRadius, config.particleMass)),
            dimensionX(config.dimensionX),
            dimensionY(config.dimensionY),
            nparticles(config.particleCount),
            particles(particles_storage)
    {
        assert(config.particleRadius > 0 
            && "Particle radius must be positive");
        assert(config.particleRadius <= 0.5 
            && "Particle radius must be less than or equal to 0.5");
        assert(dimensionX * dimensionY >= nparticles 
            && "Container must be large enough to fit all particles without overlap");

        initParticlesPositions(dimensionX, dimensionY, particles);
        initParticlesVelocities(particles);
    }


    void Model::initParticlesPositions(const int sizeX, const int sizeY, std::span<Particle> particles)
    {
        assert(particles.size() <= sizeX * sizeY 
            && "Container must be large enough to fit all particles without overlap");

        std::vector<int> cells(sizeX * sizeY);
        std::iota(cells.begin(), cells.end(), 0);

        std::shuffle(cells.begin(), cells.end(), gen);

        for (size_t i = 0; i < particles.size(); ++i) {
            int cell = cells[i];
            int x = cell % sizeX;
            int y = cell / sizeX;

            particles[i].x = x + 0.5;
            particles[i].y = y + 0.5;
        }
    }


    void Model::initParticlesVelocities(std::span<Particle> particles) {
        std::uniform_real_distribution<double> dist(0.0, 2.0 * std::numbers::pi);

        for (auto& p: particles) {
            double angle = dist(gen);
            p.vx = std::cos(angle);
            p.vy = std::sin(angle);

            assert(std::abs(std::sqrt(sqr(p.vx) + sqr(p.vy)) - 1.0) < 1e-10 && "Initial velocity must have magnitude 1");
        }
    }
}

// EOF