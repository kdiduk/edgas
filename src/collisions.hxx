#ifndef EDGAS_COLLISIONS_HXX
#define EDGAS_COLLISIONS_HXX

#include "event.hxx"
#include "particle.hxx"

namespace edgas::collisions
{
    double timeToParticleCollision(const Particle& p1, const Particle& p2);
}

#endif // EDGAS_COLLISIONS_HXX
