#ifndef ENEMY_H
#define ENEMY_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include <iostream>
#include <vector>
#include <string>

namespace game {

  class Enemy : public engine::GameObject {

    public:
      Enemy(std::string pname, std::pair<int, int> position, int priority): engine::GameObject(pname, position, priority, {{}}){};
      ~Enemy(){};

      virtual void move(GameEvent){};
      virtual void update(unsigned){};
      virtual void on_collision(engine::GameObject*, engine::Hitbox*, engine::Hitbox*){};
  };

}

#endif
