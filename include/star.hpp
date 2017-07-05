#ifndef STAR_H
#define STAR_H

#include <iostream>

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/hitbox.hpp"
#include "../engine/include/observable.hpp"
#include "../engine/include/animation.hpp"
#include <iostream>
#include <vector>
#include <string>

namespace mindscape {
  class Star : public engine::GameObject {
    private:
      void initialize_hitboxes();
      void initialize_animations();
      void initialize_audio_effects();
      engine::Animation* create_animation(
        std::string path,
        int sprite_lines,
        int sprite_columns,
        double duration,
        std::string direction
      );

    public:
      Star(std::string name, std::pair<int, int> position, int priority);
      ~Star(){};

      void on_event(GameEvent game_event);
      void on_collision(engine::GameObject*, engine::Hitbox*, engine::Hitbox*);
      void they_got_me();
  };

}

#endif
