#ifndef ANIMATION_H
 #define ANIMATION_H

 # include <string>
 #include "image.hpp"
 #include "time.hpp"
 #include "timer.hpp"

 namespace engine{

     class Animation : public Image{

     protected:

      //Construtor de image
      int is_active = false;
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


     public:

       Animation(SDL_Renderer* p_renderer,
                        std::string path,
                        bool isactive,
                        std::pair<int, int> displacement,
                        int a_render_priority,
                        unsigned int a_sprite_lines=1,
                        unsigned int a_sprite_columns=1,
                        double _duration_of_animation =1.0,
                        bool _in_loop = true)
       : Image(p_renderer, path, true, displacement,a_render_priority), sprite_lines(a_sprite_lines),
         sprite_columns(a_sprite_columns), duration_of_animation(_duration_of_animation * 1000), in_loop(_in_loop),
         total_sprites(a_sprite_lines * a_sprite_columns),first_sprite(0), final_sprite(total_sprites-1),
         actual_sprite(first_sprite), is_finished(false){ time = new Timer(); }

       virtual ~Animation(){}

       bool load();
       bool set_frame_time();
       void draw(int, int);
     };
 }

 #endif