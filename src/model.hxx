#ifndef EDGAS_MODEL_HXX
#define EDGAS_MODEL_HXX

#include <vector>

#include "particle.hxx"

namespace edgas
{
    struct Config;

    struct Model {
        int dimensionX;
        int dimensionY;
        int nparticles;
        std::vector<Particle> particles;
        double globalTime = 0.0;

        Model(const Config& config);
    };

} // namespace edgas


#endif // EDGAS_MODEL_HXX