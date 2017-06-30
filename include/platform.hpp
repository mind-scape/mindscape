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
    private:
      void initialize_image();
      void initialize_animations();
    public:
      Platform(
        std::string p_name,
        std::pair<int, int> position,
        int priority);

      ~Platform(){};

      void on_event(GameEvent game_event);
  };
}

#endif
