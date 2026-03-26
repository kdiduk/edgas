#ifndef EDGAS_STATISTICS_COLLECTOR_HXX
#define EDGAS_STATISTICS_COLLECTOR_HXX

#include "event.hxx"

namespace edgas
{
    struct StatisticsCollector
    {
        int totalWallCollisions = 0;
        int leftWallCollisions = 0;
        int rightWallCollisions = 0;
        int topWallCollisions = 0;
        int bottomWallCollisions = 0;

        void addWallCollision(double time, Wall wall)
        {
            totalWallCollisions++;
            switch (wall) {
                case Wall::Left:
                    leftWallCollisions++;
                    break;
                case Wall::Right:
                    rightWallCollisions++;
                    break;
                case Wall::Top:
                    topWallCollisions++;
                    break;
                case Wall::Bottom:
                    bottomWallCollisions++;
                    break;
                default:
                    break;
            }
        }

        void reset()
        {
            totalWallCollisions = 0;
            leftWallCollisions = 0;
            rightWallCollisions = 0;
            topWallCollisions = 0;
            bottomWallCollisions = 0;
        }
    };
}

#endif // EDGAS_STATISTICS_COLLECTOR_HXX