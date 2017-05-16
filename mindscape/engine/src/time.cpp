#include "time.hpp"

using namespace engine;

unsigned Time::m_time_elapsed;
unsigned Time::m_last_update;
state Time::m_current_state;

unsigned Time::time_elapsed() {
    if(Time::m_current_state == RUNNING) {
        unsigned now = real_time_elapsed();
        update_time(now);
    }
    return m_time_elapsed;
}

unsigned Time::real_time_elapsed() {
  return SDL_GetTicks();
}

void Time::pause_timer() {
    if(Time::m_current_state == RUNNING) {
        unsigned now = real_time_elapsed();
        update_time(now);
        Time::m_current_state = PAUSED;
    }
}

void Time::resume_timer() {
    if(Time::m_current_state == PAUSED) {
        unsigned now = real_time_elapsed();
        m_last_update = now;
        Time::m_current_state = RUNNING;
    }
}

void Time::update_time(unsigned now) {
    m_time_elapsed += now - m_last_update;
    m_last_update = now;
}
