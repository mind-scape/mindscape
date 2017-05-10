#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include "component.hpp"
#include "../../include/game_event.hpp"

namespace engine {

  class GameObject{
    public:
      std::string name;
      std::vector<Component*> audios;
      std::vector<Component*> images;
      std::vector<Component*> texts;
      std::pair<int,int> position;
      std::map<int,std::string> translations;

      GameObject();
      GameObject(std::string p_name, std::pair<int, int> p_position):name(p_name),
                                                              position(p_position){};
      ~GameObject(){};

      bool load();
      virtual void free(){};
      void draw();
      void add_component(std::string, Component*);
      virtual void on_event();
  };

}

#endif
