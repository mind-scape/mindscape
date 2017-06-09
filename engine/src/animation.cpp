 #include <cmath>
 #include "../include/animation.hpp"
 #include "../include/game.hpp"

 using namespace engine;

bool Animation::load(){

    time_of_sprite = (int) std::ceil(double(duration_of_animation) /double(total_sprites));
     std::cout << "total duration " << duration_of_animation << std::endl;
     std::cout << "total colunas  " << sprite_columns << std::endl;
     std::cout << "total linhas  " << sprite_lines << std::endl;
     std::cout << "total sprites  " << total_sprites << std::endl;
     std::cout << "tempo por sprite  " << time_of_sprite << std::endl;

    aux_time = 0;
    is_active = true;

    Image::load();
    time->init_timer();
    return true;
}

void Animation::draw(int x, int y){

      is_finished = false;
      playing_duration_of_animation += time->get_elapsed_time() - aux_time;
      aux_time = time->get_elapsed_time();

      if(playing_duration_of_animation >= duration_of_animation){
        is_finished = true;
        if(in_loop){
          playing_duration_of_animation = playing_duration_of_animation - duration_of_animation;
        } else {
          playing_duration_of_animation = duration_of_animation;
        }
      }

      //std::cout << "Tempo decorrido:  " << playing_duration_of_animation << std::endl;

      actual_sprite = (playing_duration_of_animation / time_of_sprite) + first_sprite;
      //std::cout << "Sprite atual:  " << actual_sprite << std::endl;

      int actual_line = actual_sprite / sprite_columns;
      int actual_column  = actual_sprite % sprite_columns;
      //std::cout << "Linha atual:  " << actual_line << std::endl;
      //std::cout << "Coluna atual:  " << actual_column << std::endl;

      coordinatesOnTexture.first = actual_column * dimensionOnTexture.first;
       //std::cout << "EM X:  " << coordinatesOnTexture.first << std::endl;
      coordinatesOnTexture.second = actual_line * dimensionOnTexture.second;
       //std::cout << "EM Y:  " << coordinatesOnTexture.second << std::endl;

    Image::draw(x,y);
}