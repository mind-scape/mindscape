#ifndef ANIMATION_H
#define ANIMATION_H

# include <string>
#include "image.hpp"

namespace engine{

    class Animation : public Image{

    public:
        Animation(std::string sprite_path = "",
                        unsigned int a_sprite_columns=1,
                        unsigned int a_sprite_rows=1,
                        double duration=1.0,
                        bool a_in_loop = true)

            :Image(sprite_path), sprite_columns(a_sprite_columns), sprite_rows(a_sprite_rows),
             animation_duration(static_cast<unsigned int>(duration * 1000)), in_loop(a_in_loop),
             number_frames(a_sprite_rows * a_sprite_columns), animation_duration(0), initial_frame(0),
             final_frame(number_frames - 1), atual_frame(initial_frame), is_finished(false){}

              virtual ~Animation(){}

              virtual bool load();
              virtual void free();
              virtual bool draw(int, int){}

              inline void set_range(unsigned int a_initial_frame, unsigned int a_final_frame){
                initial_frame = a_initial_frame;
                final_frame = a_final_frame;
              }

              inline void set_init_frame(unsigned int a_initial_frame){
                initial_frame = a_initial_frame;
              }

              inline void set_final_frame(unsigned int a_final_frame){
                final_frame = a_final_frame;
              }

              inline bool finished() const {return finished;}

    protected:

        unsigned int sprite_columns;
        unsigned int sprite_rows;
        unsigned int duration;
        bool in_loop;
        unsigned number_frames;

        unsigned int animation_duration;
        unsigned int frame_time;
        unsigned int initial_frame;
        unsigned int final_frame;
        unsigned int atual_frame;
        unsigned int sprite_widht;
        unsigned int sprite_height;

        bool is_finished;


    }

}


#endif