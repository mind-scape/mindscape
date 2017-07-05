#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>
#include <map>
#include "game_object.hpp"
#include "image.hpp"
#include "time.hpp"
#include "timer.hpp"
#include <vector>

namespace engine{
  class Animation : public Component {
    public:
      typedef enum Direction {
        RIGHT, LEFT
      } Direction;

    private:
      std::vector<Image *> images;
      std::vector<Image *>::iterator actual_sprite;
      int sprite_time;
      bool in_loop;
      bool finished = false;
      Direction direction;

    public:
      Animation(
      std::string name,
      std::string path,
      std::pair<int, int> displacement,
      double p_duration_of_animation,
      std::pair<int, int> sprite_sheet_size,
      std::pair<int, int> sprite_size,
      Direction p_direction,
      int priority = 1);

      virtual ~Animation(){}
      void initialize_images(std::string, std::pair<int, int>, std::pair<int, int>);
      bool load();
      void draw(int, int);
      void next();
      bool is_finished();
      void finish();
      bool is_in_loop();
      void deactivate_loop();
      void set_sprites_order(int, std::string);
      bool is_end_of_sprites();
      void setup_direction();
  };
}

#endif
