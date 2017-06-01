#ifndef HITBOX_H
#define HITBOX_H

#include <string>
#include <iostream>

#include "SDL2basics.hpp"
#include "component.hpp"

namespace engine{

  class Hitbox : public Component{
    private:
      SDL_Rect hitbox;

    public:
      Hitbox(SDL_Rect box,
        std::pair<int, int> placement,
        bool active)
        :hitbox(box),
        Component("hitbox", placement, active, 5){};

      ~Hitbox(){};

      SDL_Rect get_hitbox();
      void set_hitbox(std::pair<int, int>, std::pair<int, int>);

  };
}

#endif
