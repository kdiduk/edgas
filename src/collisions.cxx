#include "collisions.hxx"

#include <cassert>
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


    void collideParticles(Particle& p1, Particle& p2)
    {
        assert(abs(p1.t - p2.t) < 1e-8); // Ensure particles are at the same local time.
        assert((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) <= (p1.radius + p2.radius) * (p1.radius + p2.radius) + 1e-8); // Ensure particles are colliding.

        const double dx = p2.x - p1.x;
        const double dy = p2.y - p1.y;

        const double dvx = p2.vx - p1.vx;
        const double dvy = p2.vy - p1.vy;

        const double drr = dx * dx + dy * dy;
        const double dvr = dvx * dx + dvy * dy;

        const double gamma = 2.0 * dvr / ((p2.mass + p1.mass) * drr);

        const double d1 = gamma * p2.mass;
        p1.vx += d1 * dx;
        p1.vy += d1 * dy;

        const double d2 = gamma * p1.mass;
        p2.vx -= d2 * dx;
        p2.vy -= d2 * dy;
    }
}
