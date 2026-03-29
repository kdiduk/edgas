#ifndef EDGAS_COLLISIONS_HXX
#define EDGAS_COLLISIONS_HXX

#include "event.hxx"
#include "particle.hxx"

namespace edgas::collisions
{
    // Checks if two particles will collide and returns the time of collision.
    // If they won't collide, returns infinity.
    // If they collide, returns the time of the collision relative to the local time 
    // of the particle with the later local time. That is, if p1.t < p2.t, 
    // the returned time is p2.t + dt.
    double timeToParticleCollision(const Particle& p1, const Particle& p2);
}

#endif // EDGAS_COLLISIONS_HXX
