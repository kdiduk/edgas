#ifndef EDGAS_PARTICLE_HXX
#define EDGAS_PARTICLE_HXX

namespace edgas
{
    struct Particle
    {
        double x;
        double y;
        double vx;
        double vy;
        double radius;
        double mass;
        double t = 0.0; // Local time of the particle.
    };
}

#endif // EDGAS_PARTICLE_HXX