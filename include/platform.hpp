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

namespace engine {

  class Platform : public GameObject {
    public:
      Platform(std::string p_name, std::pair<int, int> position, int p):GameObject(p_name, position, p,
      {
          {KeyboardEvent::LEFT,"MOVE_LEFT"},
          {KeyboardEvent::RIGHT,"MOVE_RIGHT"},
      }){};

    ~Platform(){};

      void update();
      void on_event(GameEvent game_event);

  };

}

#endif
