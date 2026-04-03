#ifndef EDGAS_MODEL_HXX
#define EDGAS_MODEL_HXX

#include <vector>

#include "event.hxx"
#include "particle.hxx"

namespace edgas
{
    struct Model {
        int dimensionX;
        int dimensionY;
        int nparticles;
        std::vector<Particle> particles;
        std::vector<Event> events;
        double globalTime = 0.0;
    };

} // namespace edgas


#endif // EDGAS_MODEL_HXX