#ifndef TIME_H
#define TIME_H

namespace engine {
  typedef enum {RUNNING, PAUSED} state;

  class Time {
    public:
      virtual ~Time() = default;
      unsigned time_elapsed();
      void pause_timer();
      void resume_time();

    protected:
      unsigned m_time_elapsed;
      unsigned m_last_update;
      state m_current_statue;

      virtual unsigned real_time_elapsed() const = 0;
      void update_time(unsigned now);
  };
}

#endif
