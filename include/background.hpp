//TODO discover how overwrite static attribute

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include "globals.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace mindscape {
  class Background : public engine::GameObject {
    private:
      int paralax = 0;

    public:
      Background(
        std::string name,std::pair<int, int> position, int priority)
        :engine::GameObject(name, position, priority,
          {{engine::KeyboardEvent::LEFT,"MOVE_LEFT"},
           {engine::KeyboardEvent::RIGHT,"MOVE_RIGHT"}}
        ){};
      ~Background(){};
      void on_event(GameEvent game_event);
      void set_paralax(int);
      int get_paralax();
  };
}

#endif
