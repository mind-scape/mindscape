#ifndef FIGHTER_H
#define FIGHTER_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include <iostream>
#include <vector>
#include <string>

namespace mindscape {
  class Fighter {
    public:
      virtual void attack(){};
      virtual void die(engine::GameObject*){};
  };

}

#endif
