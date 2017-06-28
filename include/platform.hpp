//TODO discover how overwrite static attribute

#ifndef PLATFORM_H
#define PLATFORM_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace mindscape {
  class Platform : public engine::GameObject {
    public:
      Platform(
        std::string p_name,
        std::pair<int, int> position,
        int priority)
        :engine::GameObject(
          p_name,
          position,
          priority,
          {
            {engine::KeyboardEvent::LEFT,"MOVE_LEFT"},
            {engine::KeyboardEvent::RIGHT,"MOVE_RIGHT"},
          }
        ){};

    ~Platform(){};

      void on_event(GameEvent game_event);
  };
}

#endif
