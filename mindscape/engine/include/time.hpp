#ifndef TIME_H
#define TIME_H

#include <SDL2/SDL.h>

namespace engine {
  typedef enum {RUNNING, PAUSED} state;

  class Time {
    protected:
      unsigned m_time_elapsed;
      unsigned m_last_update;
      state m_current_state;

      unsigned real_time_elapsed();
      void update_time(unsigned now);

    public:
      virtual ~Time() = default;
      unsigned time_elapsed();
      void pause_timer();
      void resume_timer();
  };
}

#endif
