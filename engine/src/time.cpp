#include "time.hpp"

using namespace engine;

unsigned Time::now;
unsigned Time::last_time;

unsigned Time::m_time_elapsed;
unsigned Time::m_last_update;
state Time::m_current_state;

void Time::init(){
  now = SDL_GetTicks();
  last_time = SDL_GetTicks();
}

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

void Time::update_delta(){
  last_time = now;
  now = SDL_GetTicks();
}

unsigned Time::get_delta(){
  return now - last_time;
}
