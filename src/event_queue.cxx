#include "event_queue.hxx"

#include <boost/heap/binomial_heap.hpp>
#include <functional>


namespace edgas {

    struct Comparator {
        const std::vector<Event>& _events;

        explicit Comparator(const std::vector<Event>& events) : _events(events) {}

        bool operator()(size_t lhs, size_t rhs) const
        {
            return _events[lhs].time > _events[rhs].time;
        }
    };

    typedef boost::heap::binomial_heap<size_t, boost::heap::compare<Comparator>> Heap;

    struct EventQueue::Impl {

        Comparator comparator;
        Heap heap;
        std::vector<Heap::handle_type> handles;

        explicit Impl(const std::vector<Event>& events)
            :   comparator{events},
                heap{comparator}
        {

        }

    };

    EventQueue::EventQueue(const std::vector<Event>& events)
    {
        impl = std::make_unique<EventQueue::Impl>(events);

        impl->handles.reserve(events.size());
        for (size_t i = 0; i < events.size(); i++) {
            impl->handles.push_back(
                impl->heap.push(i)
            );
        }
    }

    void EventQueue::update(int i)
    {
        impl->heap.update(impl->handles[i]);
    }

    int EventQueue::top() const
    {
        return static_cast<int>(impl->heap.top());
    }

} // namespace edgas

// EOF