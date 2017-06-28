//TODO discover how overwrite static attribute

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace mindscape {
  class Background : public engine::GameObject {
    public:

      int paralax = 10;

      Background(
        std::string p_name,
        std::pair<int, int> position, int p)
        :engine::GameObject(
          p_name,
          position, p,
          {
            {engine::KeyboardEvent::LEFT,"MOVE_LEFT"},
            {engine::KeyboardEvent::RIGHT,"MOVE_RIGHT"},
          }
        ){};
      ~Background(){};
      void on_event(GameEvent game_event);
  };
}

#endif
