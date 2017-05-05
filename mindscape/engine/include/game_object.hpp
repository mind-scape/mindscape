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
      std::vector<Component*> audios;
      std::vector<Component*> images;
      std::vector<Component*> texts;
      std::pair<int,int> position;

      GameObject();
      GameObject(std::string p_name, std::pair<int, int> posi):name(p_name),
                                                              position(posi){};
      ~GameObject(){};

      bool load();
      virtual void free(){};
      void draw();
      void add_component(std::string, Component*);
  };

}

#endif
