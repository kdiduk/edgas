#ifndef EDGAS_EVENT_HXX
#define EDGAS_EVENT_HXX

#include <limits>

namespace edgas
{
    enum class Wall {
        None,
        Left,
        Right,
        Top,
        Bottom
    };

    struct Event {
        double time = std::numeric_limits<double>::infinity();
        Wall wall = Wall::None;
    };

}

#endif // EDGAS_EVENT_HXX