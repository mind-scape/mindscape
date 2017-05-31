//TODO discover how overwrite static attribute

#ifndef BUTTON_H
#define BUTTON_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/game.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

  class Button : public engine::GameObject {
    public:
      Button(std::string p_name, std::pair<int, int> position, int p):GameObject(p_name, position, p,
      {
          {71,"ENTER"},
          {72,"ENTER"},
          {73,"ENTER"},
          {74,"ENTER"},
      }){};

      ~Button(){};

      bool load();
      void free();
      void update();
      void on_event(GameEvent game_event);

  };

#endif
