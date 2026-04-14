#ifndef EDGAS_MODEL_HXX
#define EDGAS_MODEL_HXX

#include <vector>
#include <span>

#include "particle.hxx"

namespace edgas
{
    struct Config;

    class Model {
        std::vector<Particle> particles_storage;
    public:
        const int dimensionX;
        const int dimensionY;
        const int nparticles;
        std::span<Particle> particles;
        double globalTime = 0.0;

        void moveToTime(double newTime);

        Model(const Config& config);

    protected:
        static void initParticlesPositions(const int sizeX, const int sizeY, /*in-out*/ std::span<Particle> particles);

        // Initialize random velocity of magnitude 1 in a random direction
        static void initParticlesVelocities(std::span<Particle> particles);
    };

} // namespace edgas


#endif // EDGAS_MODEL_HXX