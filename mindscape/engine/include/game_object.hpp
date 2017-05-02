#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "component.hpp"

namespace engine {

  class GameObject{
    public:
      std::string name;
      std::unordered_map< std::string ,std::vector<Component *> > components;
      std::pair<int,int> position;

      GameObject();
      GameObject(std::string p_name):name(p_name){};
      ~GameObject(){};

      virtual bool load(){};
      virtual void free(){};
      void add_component(Component* component);
  };

}

#endif
