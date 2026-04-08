#ifndef EDGAS_CONFIG_HXX
#define EDGAS_CONFIG_HXX

#include <memory>
#include <string>


namespace edgas {
    struct Config {
        int particleCount;
        double particleRadius;
        double particleMass = 1.0;
        int dimensionX;
        int dimensionY;

        static std::unique_ptr<Config> from_file(const std::string& fileName);
    };
}

#endif // EDGAS_CONFIG_HXX
