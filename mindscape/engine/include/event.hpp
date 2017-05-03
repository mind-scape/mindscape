#ifndef ENGINE_EVENT_H
#define ENGINE_EVENT_H

#include <string>
#include <utility>

using std::pair;
using std::string;

namespace engine {

    class Event {
    public:
        Event(unsigned t) : m_timestamp(t) {}
        virtual ~Event() = default;

        unsigned timestamp() const { return m_timestamp; }
        void set_timestamp(unsigned t) { m_timestamp = t; }

    private:
        unsigned m_timestamp;
    };
}

#endif
