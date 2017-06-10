//TODO Check if it's correct maintain all below methods as static

#ifndef TIME_H
#define TIME_H

#include <SDL2/SDL.h>

namespace engine {
  typedef enum {RUNNING, PAUSED} state;

  class Time {
    public:
      virtual ~Time() = default;
      static unsigned time_elapsed();
      static void pause_timer();
      static void resume_timer();
      static unsigned real_time_elapsed();
      static void update_time(unsigned now);
      static void init();
      static void update_delta();
      static unsigned get_delta();
    protected:
      static unsigned last_time;
      static unsigned now;
      static unsigned m_time_elapsed;
      static unsigned m_last_update;
      static state m_current_state;

  };
}

#endif
