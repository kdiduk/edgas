#include <cassert>
#include <cmath>

#include "math.hxx"
#include "model.hxx"
#include "config.hxx"


namespace edgas {

    Model::Model(const Config& config)
        : dimensionX(config.dimensionX),
          dimensionY(config.dimensionY),
          nparticles(config.particleCount),
          particles(config.particleCount)
    {
        assert(config.particleRadius > 0 && "Particle radius must be positive");
        assert(config.particleRadius <= 0.5 && "Particle radius must be less than or equal to 0.5");

        int x = 0;
        int y = 0;

        for (auto& p: particles) {
            p.radius = config.particleRadius;
            p.mass = config.particleMass;

            p.x = (x++ % dimensionX) + 0.5;
            p.y = (y++ % dimensionY) + 0.5;

            // Initialize random velocity of magnitude 1 in a random direction
            double angle = static_cast<double>(rand()) / RAND_MAX * 2.0 * M_PI;
            p.vx = std::cos(angle);
            p.vy = std::sin(angle);

            assert(std::abs(std::sqrt(sqr(p.vx) + sqr(p.vy)) - 1.0) < 1e-10 && "Initial velocity must have magnitude 1");
        }
    }
}

// EOF