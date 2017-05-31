#ifndef SELECT_ARROW_H
#define SELECT_ARROW_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/text.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace engine{

  class SelectArrow : public GameObject{
    public:

      int arrow_seletor = 0;
      bool enter_handler = false;
      char option_select = 'z';

      SelectArrow(std::string p_name, std::pair<int, int> position, int p):GameObject(p_name, position, p,
      {
          {74,"UP"},
          {73,"DOWN"},
          {3,"ENTER"}
      }){};

      ~SelectArrow(){};

      bool load();
      void free();
      void update();
      void on_event(GameEvent game_event);

  };
}

#endif