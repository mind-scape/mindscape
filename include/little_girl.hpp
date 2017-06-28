//TODO discover how overwrite static attribute
//TODO remove littlegirl from namespace engine

#ifndef LITTLE_GIRL_H
#define LITTLE_GIRL_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
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

    public:
      LittleGirl(
        std::string name,
        std::pair<int, int> position,
        int priority)
        :engine::GameObject(
          name,
          position,
          priority,
          {
            {engine::KeyboardEvent::LEFT,"MOVE_LEFT"},
            {engine::KeyboardEvent::RIGHT,"MOVE_RIGHT"},
            {engine::KeyboardEvent::UP,"JUMP"},
            {engine::KeyboardEvent::DOWN,"CROUCH"}
          }
        ){
          //[FIXME] should be in the .cpp file
          states.set_state("X_STATE","LOOKING_RIGHT");
          states.set_state("Y_STATE","ON_GROUND");
        };

      ~LittleGirl(){};

      void on_event(GameEvent);
      void on_collision(engine::GameObject*, engine::Hitbox*, engine::Hitbox*);
      void update_state();
  };
}
#endif
