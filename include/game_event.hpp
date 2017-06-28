#ifndef GAME_EVENT_H
#define GAME_EVENT_H

#include <string>
#include "../engine/include/keyboard_event.hpp"

class GameEvent{
    public:
      GameEvent(
        std::string p_solver,
        std::string p_game_event_name,
        engine::KeyboardEvent::State p_state)
        :solver(p_solver),
        game_event_name(p_game_event_name),
        state(p_state){}

      ~GameEvent(){}

      std::string solver;
      std::string game_event_name;
      engine::KeyboardEvent::State state;
};

#endif

