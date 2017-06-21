#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include "image.hpp"
#include "time.hpp" 
#include "timer.hpp"
#include <vector>
#include <map>

namespace engine{

  class Animation : public Image{

    protected:

      //Construtor de image
      std::pair<int, int> displacement;
      int render_priority;
      //Atributos da animação
      int sprite_columns;
      int sprite_lines;
      int first_sprite;
      int final_sprite;
      int total_sprites;
      int actual_sprite;
      int time_of_sprite;
      int playing_duration_of_animation = 0;
      int duration_of_animation;
      bool in_loop = false;
      bool is_finished;
      //Atributo para o timer;
      Timer * time;
      int aux_time;
      std::vector<std::pair<int,int> > sprites_sizes;
      bool use_default_image_size = true;
      std::string direction;
      std::map<int,int> sprites_order;

    public:

      void set_sprites_order(int, std::string);
      Animation(SDL_Renderer* p_renderer,
          std::string path,
          bool is_active,
          std::pair<int, int> displacement,
          int p_render_priority,
          unsigned int p_sprite_lines=1,
          unsigned int p_sprite_columns=1,
          double p_duration_of_animation =1.0,
          bool p_in_loop = true,
          std::string p_direction="RIGHT",
          bool p_use_default_image_size = true)
        : Image(p_renderer, path, is_active, displacement,p_render_priority), sprite_lines(p_sprite_lines),
        sprite_columns(p_sprite_columns), duration_of_animation(p_duration_of_animation * 1000), in_loop(p_in_loop),
        total_sprites(p_sprite_lines * p_sprite_columns),first_sprite(0), final_sprite(total_sprites-1),
        actual_sprite(first_sprite), is_finished(false), use_default_image_size(p_use_default_image_size), direction(p_direction) { 
          time = new Timer(); 
          set_sprites_order(total_sprites,direction);
        }

      virtual ~Animation(){}

      bool load();
      bool set_frame_time();
      void draw(int, int);
      void set_sprite_sizes(std::vector<std::pair<int,int> >);
  };
}

#endif
