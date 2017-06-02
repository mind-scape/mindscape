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
        std::pair<int, int> go_coordinates,
        std::pair<int, int> displacement,
        std::pair<int, int> dimensions,
        bool active = true,
        int priority = 5)
        :hitbox({go_coordinates.first + displacement.first,
                 go_coordinates.second + displacement.second ,
                 dimensions.first, dimensions.second}),
        Component(name, displacement, active, priority){};

      ~Hitbox(){};

      std::pair<int, int> get_dimensions();
      void set_dimensions(std::pair<int, int>);
      bool collides_with(Hitbox*);
      void set_displacement(std::pair<int, int>, std::pair<int, int>);
      std::pair<int, int> get_coordinates();
      void update(std::pair<int, int>);
  };
}

#endif
