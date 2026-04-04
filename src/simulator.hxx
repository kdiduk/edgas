#ifndef EDGAS_SIMULATOR_HXX
#define EDGAS_SIMULATOR_HXX

#include <vector>

#include "event.hxx"
#include "model.hxx"
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
        void findNextEvent(int i);

        Event findNextWallCollision(int i) const;
        Event findNextParticleCollision(int i) const;

        int getNextEvent() const;

        void processNextEvent();

        void processNextWallCollisionEvent(int i);
        void processNextParticleCollisionEvent(int i, int j);

        void processWallCollision(const Event& event);
        void processParticleCollision(const Event& event);

        Model model;
        std::vector<Event> events;
        SnapshotWriter snapshotWriter{"snapshots.txt"};
        StatisticsCollector statisticsCollector;
    };
}

#endif // EDGAS_SIMULATOR_HXX