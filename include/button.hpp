//TODO discover how overwrite static attribute

#ifndef BUTTON_H
#define BUTTON_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/keyboard_event.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

  class Button : public engine::GameObject {
    public:
      Button(std::string p_name, std::pair<int, int> position, int p):GameObject(p_name, position, p,
      {
          {engine::KeyboardEvent::RETURN,"ENTER"},
      }){};

      ~Button(){};

      void on_event(GameEvent game_event);

  };

#endif
