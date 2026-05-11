#ifndef EDGAS_EVENT_QUEUE_HXX
#define EDGAS_EVENT_QUEUE_HXX

#include <memory>
#include <vector>
#include "event.hxx"


namespace edgas {

class EventQueue final {
public:

    explicit EventQueue(const std::vector<Event>& events);
    ~EventQueue();

    void update(int i);

    int top() const;

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

} // namespace edgas

#endif // EDGAS_EVENT_QUEUE_HXX