#ifndef EDGAS_PARTICLE_HXX
#define EDGAS_PARTICLE_HXX

namespace edgas
{
    struct Particle
    {       
        const double radius;
        const double mass;

        double x = 0.0;
        double y = 0.0;
        double vx = 0.0;
        double vy = 0.0;
        double t = 0.0; // Local time of the particle.

        Particle(double r, double m = 1.0) : radius(r), mass(m) { }
    };
}

#endif // EDGAS_PARTICLE_HXX