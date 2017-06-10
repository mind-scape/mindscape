//TODO discover how overwrite static attribute
//TODO remove littlegirl from namespace engine

#ifndef LITTLE_GIRL_H
#define LITTLE_GIRL_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using std::string;

namespace engine {

  class LittleGirl : public GameObject {
    public:

      bool on_floor = true;
      int animation_count = 0;
      int animation_count2 = 0;


      LittleGirl(std::string p_name, std::pair<int, int> position, int p):GameObject(p_name, position, p,
      {
          {KeyboardEvent::LEFT,"MOVE_LEFT"},
          {KeyboardEvent::RIGHT,"MOVE_RIGHT"},
          {KeyboardEvent::UP,"JUMP"},
          {KeyboardEvent::DOWN,"CROUCH"},
      }){};
      ~LittleGirl(){};

      void update(unsigned);
      void on_event(GameEvent);
      void on_collision(GameObject*, Hitbox*, Hitbox*);
  };

}

#endif
