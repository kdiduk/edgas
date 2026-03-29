#ifndef EDGAS_SIMULATOR_HXX
#define EDGAS_SIMULATOR_HXX

#include <vector>

#include "event.hxx"
#include "particle.hxx"
#include "snapshot_writer.hxx"
#include "statistics_collector.hxx"

namespace edgas
{
    struct Config;

    class Simulator
    {
    public:
        Simulator(const Config& config);

        void step();

        const StatisticsCollector& getStatistics() const;

    private:
        void findNextEvent();
        void processNextEvent();

        int dimensionX = 0;
        int dimensionY = 0;
        Particle particle;
        double currentTime = 0.0;
        Event nextEvent;
        SnapshotWriter snapshotWriter{"snapshots.txt"};
        StatisticsCollector statisticsCollector;
    };
}

#endif // EDGAS_SIMULATOR_HXX