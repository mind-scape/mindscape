#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <list>
#include "keyboard_event.hpp"
#include "translator.hpp"

namespace engine{

  class EventHandler {
    public:
      EventHandler();
      ~EventHandler();

      void dispatch_pending_events(unsigned now);
      std::list<KeyboardEvent> pending_keyboard_events(unsigned now);
      void get_events_until_now(unsigned now);

    private:
      unsigned last_update;
      std::list<SDL_Event> sdl_events;
      std::list<> listeners;
  };

}

#endif
