//TODO trocar os vectors de componentes para unordered maps

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>
#include "component.hpp"
#include "../../include/game_event.hpp"

namespace engine {

  class GameObject{
    public:
      std::string name;
      int priority;
      static bool on_limit_of_level;
      std::vector<Component*> audios;
      std::vector<Component*> images;
      std::vector<Component*> texts;
      std::pair<int,int> position;
      std::map<int,std::string> translations;
      bool active_game_object;

      GameObject(){};
      GameObject(std::string p_name, std::pair<int, int> p_position, int p):name(p_name),position(p_position), priority(p), active_game_object(false){};
      GameObject(std::string p_name, std::pair<int, int> p_position, int p, std::map<int,std::string> p_translations):name(p_name),position(p_position),active_game_object(false),priority(p), translations(p_translations){};
      ~GameObject(){};

      bool load();
      virtual void free(){};
      void draw();
      void add_component(std::string, Component*);
      virtual void on_event(GameEvent){};
  };

}

#endif
