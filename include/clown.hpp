#ifndef SCORPION_H
#define SCORPION_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/hitbox.hpp"
#include "../engine/include/observable.hpp"
#include "../engine/include/animation.hpp"
#include "enemy.hpp"
#include "boss.hpp"
#include <iostream>
#include <vector>
#include <string>

namespace mindscape {
  class Clown : public Boss {
    private:
      void initialize_boss_parts();
      void initialize_state_map();
      void initialize_hitboxes();
      void initialize_animations();
      void initialize_as_physicable();
      void on_attack();
      void attack();
      engine::Animation *create_animation(
        std::string path,
        int sprite_lines,
        int sprite_columns,
        double duration,
        std::string direction
      );

    public:
      Clown(
        std::string name,
        std::pair<int, int> position,
        int priority
      );
      ~Clown(){};

      void on_event(GameEvent);
      void on_collision(engine::GameObject*, engine::Hitbox*, engine::Hitbox*);
      void notify(engine::Observable *);
  };

}

#endif
