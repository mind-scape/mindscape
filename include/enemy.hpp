#ifndef ENEMY_H
#define ENEMY_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include "fighter.hpp"
#include <iostream>
#include <vector>
#include <string>

namespace mindscape {

  class Enemy : public engine::GameObject, public mindscape::Fighter {

    public:
      Enemy(std::string name, std::pair<int, int> position, int priority,int HP = 0): engine::GameObject(name, position, priority, {
        {engine::KeyboardEvent::LEFT,"MOVE_LEFT"},
        {engine::KeyboardEvent::RIGHT,"MOVE_RIGHT"},
      }), HP(HP){};
      ~Enemy(){};

      virtual void move(GameEvent){};
      virtual void update(unsigned){};
      virtual void on_collision(engine::GameObject*, engine::Hitbox*, engine::Hitbox*){};
      virtual void notify(engine::Observable *){};
      void update_HP(int);
      int get_HP();

    private:
      int HP;
  };

}

#endif
