#include "collisions.hxx"

#include <cmath>
#include <cstdlib>
#include <iostream>

namespace edgas::collisions
{
    double timeToParticleCollision(const Particle& p1, const Particle& p2)
    {
        if (p1.t > p2.t) {
            return timeToParticleCollision(p2, p1);
        }

        auto dt = p2.t - p1.t;
        auto x1 = p1.x + p1.vx * dt;
        auto y1 = p1.y + p1.vy * dt;

        auto dx = p2.x - x1;
        auto dy = p2.y - y1;
        auto dvx = p2.vx - p1.vx;
        auto dvy = p2.vy - p1.vy;
        auto dvr = dx * dvx + dy * dvy;

        if (dvr >= 0) {
            return std::numeric_limits<double>::infinity();
        }

        auto drr = dx * dx + dy * dy;
        auto dvv = dvx * dvx + dvy * dvy;

        auto c = drr - (p1.radius + p2.radius) * (p1.radius + p2.radius);

        if (c < 0) {
            std::cerr << "Warning: Particles are overlapping. Adding small random value to avoid numerical issues." << std::endl;
            c = 1e-8 * (1.0 + static_cast<double>(rand()) / RAND_MAX);
        }
        
        auto disc = dvr * dvr - dvv * c;
        if (disc < 0) {
            return std::numeric_limits<double>::infinity();
        }

        auto dd = std::sqrt(disc);
        auto delt = std::abs(-dvr - dd) / dvv;

        return p2.t + delt;
    }
}
