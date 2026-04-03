#ifndef EDGAS_EVENT_HXX
#define EDGAS_EVENT_HXX

#include <limits>

namespace edgas
{
    enum EventType {
        None,
        WallCollision,
        ParticleCollision
    };
    
    enum class Wall {
        None,
        Left,
        Right,
        Top,
        Bottom
    };

    struct Event {
        EventType type = EventType::None;
        double time = std::numeric_limits<double>::infinity();
        Wall wall = Wall::None;
        int otherParticle = -1;
    };

}

#endif // EDGAS_EVENT_HXX