//TODO discover how overwrite static attribute

#ifndef LITTLE_GIRL_H
#define LITTLE_GIRL_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/image.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace engine {

  class LittleGirl : public GameObject {
    public:
      LittleGirl(std::string p_name, std::pair<int, int> position, int p):GameObject(p_name, position, p,
      {
          {71,"MOVE_LEFT"},
          {72,"MOVE_RIGHT"},
          {73,"JUMP"},
          {74,"CROUCH"},
      }){};

      ~LittleGirl(){};

      bool load();
      void free();
      void update();
      void on_event(GameEvent game_event);

  };

}

#endif
