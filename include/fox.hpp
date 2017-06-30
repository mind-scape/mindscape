//TODO discover how overwrite static attribute

#ifndef FOX_H
#define FOX_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/animation.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/keyboard_event.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace mindscape {
  class Fox : public engine::GameObject {
    private:
      int velocity;
      int running_right_animation_count = 0;
      int running_left_animation_count = 0;
      
      void initialize_state_map();
      void initialize_animations();
      void initialize_as_physicable();
      engine::Animation *create_animation(
        std::string path,
        int sprite_lines,
        int sprite_columns,
        double duration,
        std::string direction
      );

    public:
      Fox(std::string p_name,std::pair<int, int> position,int priority);
      ~Fox(){};

      void on_event(GameEvent game_event);
      void update_state();
  };
}

#endif
