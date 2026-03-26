#include "simulator.hxx"
#include "config.hxx"
#include <cmath>


namespace edgas
{
    Simulator::Simulator(const Config& config)
    {
        dimensionX = config.dimensionX;
        dimensionY = config.dimensionY;

        particle.radius = config.particleRadius;
        particle.mass = config.particleMass;
        particle.x = dimensionX / 2.0;
        particle.y = dimensionY / 2.0;

        // Initialize random velocity of magnitude 1 in a random direction
        double angle = static_cast<double>(rand()) / RAND_MAX * 2.0 * M_PI;
        particle.vx = std::cos(angle);
        particle.vy = std::sin(angle);

        snapshotWriter.writeSnapshot(currentTime, particle);
        findNextEvent();
    }

    void Simulator::step()
    {
        processNextEvent();
        
        snapshotWriter.writeSnapshot(currentTime, particle);
        
        findNextEvent();
    }

    const StatisticsCollector& Simulator::getStatistics() const
    {
        return statisticsCollector;
    }

    void Simulator::findNextEvent()
    {
        double timeToVerticalWall = std::numeric_limits<double>::infinity();
        Wall nextWall = Wall::None;
        if (particle.vx > 0) {
            double timeToRightWall = (dimensionX - particle.radius - particle.x) / particle.vx;
            if (timeToRightWall < timeToVerticalWall) {
                timeToVerticalWall = timeToRightWall;
                nextWall = Wall::Right;
            }
        } else if (particle.vx < 0) {
            double timeToLeftWall = (particle.radius - particle.x) / particle.vx;
            if (timeToLeftWall < timeToVerticalWall) {
                timeToVerticalWall = timeToLeftWall;
                nextWall = Wall::Left;
            }
        }

        if (particle.vy > 0) {
            double timeToTopWall = (dimensionY - particle.radius - particle.y) / particle.vy;
            if (timeToTopWall < timeToVerticalWall) {
                timeToVerticalWall = timeToTopWall;
                nextWall = Wall::Top;
            }
        } else if (particle.vy < 0) {
            double timeToBottomWall = (particle.radius - particle.y) / particle.vy;
            if (timeToBottomWall < timeToVerticalWall) {
                timeToVerticalWall = timeToBottomWall;
                nextWall = Wall::Bottom;
            }
        }

        nextEvent.time = timeToVerticalWall;
        nextEvent.wall = nextWall;
    }

    void Simulator::processNextEvent()
    {
        currentTime += nextEvent.time;
        particle.x += particle.vx * nextEvent.time;
        particle.y += particle.vy * nextEvent.time;

        statisticsCollector.addWallCollision(currentTime, nextEvent.wall);

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
                break;
        }
    }
}
