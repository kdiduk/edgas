#include "simulator.hxx"
#include "collisions.hxx"
#include "config.hxx"
#include "particle.hxx"
#include <cmath>
#include <iostream>


namespace edgas
{
    Simulator::Simulator(const Config& config)
        : model(config)
    {
        snapshotWriter.writeSnapshot(model);

        events.resize(config.particleCount);
        for (int i = 0; i < model.nparticles; ++i) {
            findNextEvent(i);
        }
    }

    void Simulator::step()
    {
        processNextEvent();

        snapshotWriter.writeSnapshot(model);
    }

    const StatisticsCollector& Simulator::getStatistics() const
    {
        return statisticsCollector;
    }

    void Simulator::findNextEvent(int i)
    {
        Event wallCollisionEvent = findNextWallCollision(i);
        Event particleCollisionEvent = findNextParticleCollision(i);
        Event minEvent = (wallCollisionEvent.time < particleCollisionEvent.time) ? wallCollisionEvent : particleCollisionEvent;

        events[i] = minEvent;
        if (minEvent.type == EventType::ParticleCollision) {
            int j = minEvent.otherParticle;
            events[j] = minEvent;
            events[j].otherParticle = i;
        }
    }

    Event Simulator::findNextWallCollision(int i) const
    {
        const auto& particle = model.particles[i];

        double minTime = std::numeric_limits<double>::infinity();
        Wall nextWall = Wall::None;
        if (particle.vx > 0) {
            double timeToRightWall = (model.dimensionX - particle.radius - particle.x) / particle.vx;
            if (timeToRightWall < minTime) {
                minTime = timeToRightWall;
                nextWall = Wall::Right;
            }
        } else if (particle.vx < 0) {
            double timeToLeftWall = (particle.radius - particle.x) / particle.vx;
            if (timeToLeftWall < minTime) {
                minTime = timeToLeftWall;
                nextWall = Wall::Left;
            }
        }

        if (particle.vy > 0) {
            double timeToTopWall = (model.dimensionY - particle.radius - particle.y) / particle.vy;
            if (timeToTopWall < minTime) {
                minTime = timeToTopWall;
                nextWall = Wall::Top;
            }
        } else if (particle.vy < 0) {
            double timeToBottomWall = (particle.radius - particle.y) / particle.vy;
            if (timeToBottomWall < minTime) {
                minTime = timeToBottomWall;
                nextWall = Wall::Bottom;
            }
        }

        Event event = {};
        event.type = EventType::WallCollision;
        event.time = minTime + particle.t;
        event.wall = nextWall;
        return event;
    }


    Event Simulator::findNextParticleCollision(int i) const
    {
        const auto& particle = model.particles[i];

        Event event = {};
        event.type = EventType::ParticleCollision;

        for (int j = 0; j < model.nparticles; ++j) {
            if (i == j) continue;

            const auto& otherParticle = model.particles[j];
            double timeToCollision = collisions::timeToParticleCollision(particle, otherParticle);
            if (timeToCollision < event.time) {
                event.time = timeToCollision;
                event.otherParticle = j;
            }
        }

        return event;
    }


    int Simulator::getNextEvent() const
    {
        int nextEventIndex = -1;
        double minTime = std::numeric_limits<double>::infinity();

        for (int i = 0; i < model.nparticles; ++i) {
            if (events[i].time < minTime) {
                minTime = events[i].time;
                nextEventIndex = i;
            }
        }

        return nextEventIndex;
    }

    void Simulator::processNextEvent()
    {
        int i = getNextEvent();
        const auto& nextEvent = events[i];
        switch (nextEvent.type) {
            case EventType::WallCollision:
                processNextWallCollisionEvent(i);
                findNextEvent(i);
                break;
            case EventType::ParticleCollision: {
                    int j = nextEvent.otherParticle;
                    processNextParticleCollisionEvent(i, j);
                    findNextEvent(i);
                    findNextEvent(j);
                }
                break;
            default:
                std::cerr << "Unknown event type: "
                    << static_cast<int>(nextEvent.type)
                    << std::endl;
                break;
        }
    }

    void Simulator::processNextWallCollisionEvent(int i)
    {
        auto& particle = model.particles[i];
        auto& nextEvent = events[i];

        model.globalTime = nextEvent.time;
        particle.x += particle.vx * (nextEvent.time - particle.t);
        particle.y += particle.vy * (nextEvent.time - particle.t);
        particle.t = nextEvent.time;

        statisticsCollector.addWallCollision(nextEvent.wall);

        switch (nextEvent.wall) {
            case Wall::Left:
            case Wall::Right:
                particle.vx = -particle.vx;
                break;
            case Wall::Top:
            case Wall::Bottom:
                particle.vy = -particle.vy;
                break;
            default:
                std::cerr << "Warning: invalid wall collision event\n";
                break;
        }
    }

    void Simulator::processNextParticleCollisionEvent(int i, int j)
    {
        auto& particle1 = model.particles[i];
        auto& particle2 = model.particles[j];
        auto& nextEvent1 = events[i];
        auto& nextEvent2 = events[j];

        if (nextEvent1.otherParticle != j || nextEvent2.otherParticle != i) {
            std::cerr << "Warning: invalid particle collision event"
                << std::endl;
            statisticsCollector.addInvalidParticleCollision();
            return;
        }

        if (std::abs(nextEvent1.time - nextEvent2.time) > 1e-9) {
            std::cerr << "Warning: invalid particle collision event"
                << std::endl;
            statisticsCollector.addInvalidParticleCollision();
            return;
        }

        model.globalTime = nextEvent1.time;
        particle1.x += particle1.vx * (nextEvent1.time - particle1.t);
        particle1.y += particle1.vy * (nextEvent1.time - particle1.t);
        particle2.x += particle2.vx * (nextEvent2.time - particle2.t);
        particle2.y += particle2.vy * (nextEvent2.time - particle2.t);
        particle1.t = nextEvent1.time;
        particle2.t = nextEvent2.time;

        collisions::collideParticles(particle1, particle2);
        statisticsCollector.addParticleCollision();
    }
}
