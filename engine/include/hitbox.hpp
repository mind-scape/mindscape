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
      Hitbox(
        std::string name,
        std::pair<int, int> coordinates,
        std::pair<int, int> dimensions,
        bool active = true,
        int priority = 5)
        :hitbox({coordinates.first, coordinates.second,
                         dimensions.first, dimensions.second}),
        Component(name, coordinates, active, priority){};

      ~Hitbox(){};

      std::pair<int, int> get_dimensions();
      void set_dimensions(std::pair<int, int>);
      bool collides_with(Hitbox*);
      void set_coordinates(std::pair<int, int>);
  };
}

#endif
