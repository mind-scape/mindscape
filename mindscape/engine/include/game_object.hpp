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
      GameObject(){};
      GameObject(std::string p_name, std::pair<int, int> p_position):name(p_name),position(p_position),active_game_object(false){};
      GameObject(std::string p_name, std::pair<int, int> p_position,std::map<int,std::string> p_translations):name(p_name),position(p_position),active_game_object(false),translations(p_translations){};
      ~GameObject(){};

      std::string name;
      std::vector<Component*> audios;
      std::vector<Component*> images;
      std::vector<Component*> texts;
      std::pair<int,int> position;
      std::map<int,std::string> translations;
      bool active_game_object;

      bool load();
      virtual void free(){};
      void draw();
      void add_component(std::string, Component*);
      virtual void on_event(GameEvent){};
  };

}

#endif
