#ifndef ENEMY_H
#define ENEMY_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include <iostream>
#include <vector>
#include <string>

namespace game {

  class Enemy : public GameObject {

    Enemy(std::string pname, std::pair<int, int> position, int priority):GameObject(pname, position, priority, {{}}){};
    ~Enemy(){};

    virtual void move(GameEvent){};
    void update(unsigned);
  };

}

#endif
