//TODO discover how overwrite static attribute
//TODO remove littlegirl from namespace engine

#ifndef LITTLE_GIRL_H
#define LITTLE_GIRL_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/animation.hpp"
#include "../engine/include/hitbox.hpp"
#include "../engine/include/physics.hpp"
#include "fighter.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace mindscape {
  class LittleGirl : public engine::GameObject, public mindscape::Fighter {
    private:
      static LittleGirl* instance;
      //[FIXME] should be a map or deleted
      int running_right_animation_count = 0;
      int running_left_animation_count = 0;
      int jumping_animation_count = 0;
      int attacking_right_animation = 0;
      int attacking_left_animation = 0;

      void initialize_state_map();
      void initialize_hitboxes();
      void initialize_animations();
      void initialize_audio_effects();
      void initialize_as_physicable();
      void jump(std::string);
      void move_right(std::string,std::string);
      void move_left(std::string,std::string);
      void attack(std::string);
      void on_attack();
      engine::Animation *create_animation(
        std::string path,
        int sprite_lines,
        int sprite_columns,
        double duration,
        std::string direction
      );

    public:
      LittleGirl(std::string name, std::pair<int, int> position, int priority);
      ~LittleGirl(){};

      void on_event(GameEvent);
      void on_collision(engine::GameObject*, engine::Hitbox*, engine::Hitbox*);
      void update_state();
  };
}
#endif
