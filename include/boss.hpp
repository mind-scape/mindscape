#ifndef BOSS_H
#define BOSS_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include "fighter.hpp"
#include "enemy.hpp"
#include <iostream>
#include <string>
#include <map>

namespace mindscape {

  class Boss : public Enemy {
    private:
      std::map<std::string, Enemy*> boss_parts; 

    public:
      Boss(std::string name, std::pair<int, int> position, int priority,int HP = 0) : Enemy(name, position, priority, HP){};
      ~Boss(){};

      std::map<std::string, Enemy*> get_boss_parts();
      void set_boss_part(std::string, Enemy*);
      void draw();
      void activate();
  };

}

#endif
