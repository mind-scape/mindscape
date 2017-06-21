//TODO discover how overwrite static attribute

#ifndef FOX_H
#define FOX_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/keyboard_event.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace engine {

  class Fox : public GameObject {
    private:
      int velocity;
      int animation_count = 0;
      int animation_count2 = 0;

    public:
      Fox(std::string p_name, std::pair<int, int> position, int p):GameObject(p_name, position, p,
      {
          {KeyboardEvent::LEFT,"MOVE_LEFT"},
          {KeyboardEvent::RIGHT,"MOVE_RIGHT"},
          {KeyboardEvent::UP,"JUMP"},
          {KeyboardEvent::DOWN,"CROUCH"},
      }){};

      ~Fox(){};

      void on_event(GameEvent game_event);
      void update_state();

  };

}

#endif
