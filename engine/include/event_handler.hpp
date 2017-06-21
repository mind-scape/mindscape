#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <iostream>
#include "SDL2basics.hpp"
#include <list>
#include "keyboard_event.hpp"
#include "translator.hpp"
#include "game_object.hpp"
#include "game.hpp"

namespace engine{

  class EventHandler {
    private:
      unsigned last_update;
      std::list< SDL_Event > sdl_events;
      void try_to_get_delayed_keys(std::list<KeyboardEvent>&);

    public:
      static std::list <GameObject *> listeners;

      EventHandler(){};
      ~EventHandler(){};

      void dispatch_pending_events(unsigned now);
      std::list<KeyboardEvent> pending_keyboard_events(unsigned now);
      void get_events_until_now(unsigned now);
      static void add_listener(GameObject * listener);
      static void remove_listener(GameObject * listener);
  };

}

#endif
