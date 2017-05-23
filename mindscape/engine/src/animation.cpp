#include <cmath>

#include "../include/animation.hpp"
#include "../include/game.hpp"

using namespace engine;

bool Animation::load(){

    if(Image::load() == false){
        printf("\nNão está carregando a imagem no Animation\n");
        return false;
    }

    if(animation_duration == 0){
        printf("\nNão se pode criar uma animação com 0 de duração\n");
        return false;
    }

    if(sprite_columns == 0){
        printf("\nNão se pode iniciar uma animação com 0 colunas de sprites\n");
        return false;
    }

    if(sprite_rows == 0){
        printf("\nNão se pode iniciar uma animação com 0 linhas de sprites\n");
        return false;
    }

    if (initial_frame > final_frame){
        printf("\nTempo inicial da animação maior que o tempo final\n");
        return false;
    }

    number_frames = final_frame - initial_frame + 1;
    sprite_widht = dimensionOnTexture.first / sprite_columns;
    sprite_height = dimensionOnTexture.second / sprite_height;

    frame_time = (unsigned int) std::ceil(double(animation_duration)/double(number_frames))

    return true;

}

bool Animation::free(){
    if(Image::free() == false){
        printf("\nNão pôde liberar a memória da animação\n");
        return false;
    }

    return true;
}

void Animation::draw(){

    is_finished = false;

    animation_duration += Game::instance.elapsed_time();

    if(animation_duration >= duration){
        is_finished = true;

        if(in_loop){
            animation_duration -= duration;
        } else {
            animation_duration = duration;
        }
    }

    atual_frame = (animation_duration / frame_time) + initial_frame;

    int atual_row = atual_frame / sprite_columns;
    int atual_col = atual_frame % sprite_columns;



}