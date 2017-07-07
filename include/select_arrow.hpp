#ifndef SELECT_ARROW_H
#define SELECT_ARROW_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/text.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/time.hpp"
#include "../engine/include/game.hpp"
#include "action.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace mindscape {
  class SelectArrow : public engine::GameObject{
    private:
      void initialize_arrow();
      engine::Time * timer;
      float time;
      float time_aux = 0;
      float next_time = 0;
      bool enable = true;
      int arrow_seletor = 0;
      engine::Game * game = &(engine::Game::get_instance());
      Action* action;

    public:
      SelectArrow(
        std::string name,
        std::pair<int, int> position,
        int priority);
      ~SelectArrow(){};
      void on_event(GameEvent game_event);
      void add_action(Action* act);
  };
}
#endif
