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

namespace mindscape{

  class Spider : public Enemy {
    public:
      Spider(std::string p_name, std::pair<int, int> position, int p): Enemy(p_name, position, p){
        states.set_state("FIGHT_STATE","NORMAL");
      };
      ~Spider(){};

      void attack();
      void move(GameEvent);
      void on_event(GameEvent);
      void on_collision(engine::GameObject*, engine::Hitbox*, engine::Hitbox*);
  };

}

#endif
