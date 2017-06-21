#ifndef SPIDER_H
#define SPIDER_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/hitbox.hpp"
#include "enemy.hpp"
#include <iostream>
#include <vector>
#include <string>

namespace game{

  class Spider : public Enemy {
    Spider(std::string p_name, std::pair<int, int> position, int p): Enemy(p_name, position, p){};
    ~Spider(){};

    void on_event(GameEvent);
    void on_collision(engine::GameObject*, engine::Hitbox*, engine::Hitbox*);
    void update(unsigned);
  };

}

#endif
