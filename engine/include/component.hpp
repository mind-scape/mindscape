//TODO Create enum to components types

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <iostream>

namespace engine{

  class Component{
    public:
      std::string type;
      bool active;
      std::pair<int, int> displacement;

      Component(){};
      Component(std::string p_type, std::pair<int, int> place, bool isactive):type(p_type),
                                                                                displacement(place),
                                                                                active(isactive){};
      ~Component(){};

      virtual bool load(){};
      virtual void free(){};
      virtual void draw(int, int){};
    };

}

#endif
