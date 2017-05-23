#ifndef ANIMATION_H
#define ANIMATION_H

# include <string>
#include "image.hpp"
#include "time.hpp"
#include "timer.hpp"

namespace engine{

    class Animation : public Image{

    protected:

      unsigned int sprite_columns;
      unsigned int sprite_rows;

      unsigned int duration;
      unsigned int animation_duration;

      unsigned number_frames;
      unsigned int frame_time;
      unsigned int initial_frame;
      unsigned int final_frame;
      unsigned int actual_frame;

      bool in_loop;
      bool is_finished;
      engine::Timer* time;

    public:

      Animation(SDL_Renderer* p_renderer,
                std::string path,
                bool isactive,
                std::pair<int, int> displacement,
                unsigned int a_sprite_columns=1,
                unsigned int a_sprite_rows=1,
                double _duration=1.0,
                bool _in_loop = true)
      : Image(p_renderer, path, isactive, displacement), sprite_columns(a_sprite_columns),
        sprite_rows(a_sprite_rows), duration(_duration*1000), in_loop(_in_loop),
        number_frames(a_sprite_rows * a_sprite_columns), animation_duration(0), initial_frame(0),
        final_frame(number_frames-1), actual_frame(initial_frame), is_finished(false){ time = new Timer(); }

      virtual ~Animation(){}

      bool set_frame_time();
      void draw(int, int);
    };
}

#endif
