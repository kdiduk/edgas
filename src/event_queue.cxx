#include "event_queue.hxx"

#include <boost/heap/binomial_heap.hpp>


namespace edgas {

    struct QueueEntry {
        double time;
        int index;
    };

    struct Comparator {
        bool operator()(const QueueEntry& lhs, const QueueEntry& rhs) const
        {
            // min-heap on time; tie-break on index for determinism
            if (lhs.time != rhs.time) return lhs.time > rhs.time;
            return lhs.index > rhs.index;
        }
    };

    typedef boost::heap::binomial_heap<QueueEntry, boost::heap::compare<Comparator>> Heap;

    struct EventQueue::Impl {
        Heap heap;
        std::vector<Heap::handle_type> handles;
    };

    EventQueue::EventQueue(const std::vector<Event>& events)
    {
        impl = std::make_unique<EventQueue::Impl>();

        impl->handles.reserve(events.size());
        for (size_t i = 0; i < events.size(); i++) {
            impl->handles.push_back(
                impl->heap.push(QueueEntry{events[i].time, static_cast<int>(i)})
            );
        }
    }

    EventQueue::~EventQueue()
    {

    }

    void EventQueue::update(int i, double time)
    {
        (*impl->handles[i]).time = time;
        impl->heap.update(impl->handles[i]);
    }

    int EventQueue::top() const
    {
        return impl->heap.top().index;
    }

} // namespace edgas

// EOF
