#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>
#include <map>
#include "game_object.hpp"
#include "image.hpp"
#include "time.hpp"
#include "timer.hpp"

namespace engine{
  class GameObject;
  class Animation : public Image{

  private:

      //Construtor de image
      std::pair<int, int> displacement;
      int render_priority;
      GameObject* game_object;
      //Atributos da animação
      int first_sprite;
      int final_sprite;
      int time_of_sprite;
      int playing_duration_of_animation = 0;
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
          int priority,
          unsigned int p_sprite_lines=1,
          unsigned int p_sprite_columns=1,
          double p_duration_of_animation =1.0,
          bool p_in_loop = true,
          std::string p_direction="RIGHT",
          bool p_use_default_image_size = true)
        :Image(
          p_renderer,
          path,
          is_active,
          displacement,
          priority
        ),
        sprite_lines(p_sprite_lines),
        sprite_columns(p_sprite_columns),
        duration_of_animation(p_duration_of_animation*1000),
        in_loop(p_in_loop),
        total_sprites(p_sprite_lines * p_sprite_columns),
        first_sprite(0),
        final_sprite(total_sprites-1),
        actual_sprite(first_sprite),
        is_finished(false),
        use_default_image_size(p_use_default_image_size),
        direction(p_direction) {
          time = new Timer();
          set_sprites_order(total_sprites,direction);
        }

      virtual ~Animation(){}

      int actual_line;
      int actual_column;
      int actual_sprite;
      int total_sprites;
      int duration_of_animation;
      int sprite_columns;
      int sprite_lines;
      bool in_loop;
      bool is_finished;
      bool is_a_final_animation = false;

      bool load();
      bool set_frame_time();
      void set_game_object(GameObject*);
      void draw(int, int);
      void activate();
      void set_sprite_sizes(std::vector<std::pair<int,int> >);
  };
}

#endif
