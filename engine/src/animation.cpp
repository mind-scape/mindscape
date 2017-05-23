#include <cmath>

#include "../include/animation.hpp"
#include "../include/game.hpp"

using namespace engine;

bool Animation::set_frame_time(){
    frame_time = (double)(duration/number_frames);
    return true;
}

// TODO: Implement free

void Animation::draw(int x, int y){
    is_finished = false;
    animation_duration += time->get_total_time();

    if(animation_duration >= duration){
        is_finished = true;
        if(in_loop){
            animation_duration -= duration;
        } else {
            animation_duration = duration;
        }
    }

    actual_frame = (animation_duration / frame_time) + initial_frame;

    int actual_row = actual_frame / sprite_columns;
    int actual_col = actual_frame % sprite_columns;

    SDL_Rect ret = {actual_col * dimensionOnTexture.first, actual_row * dimensionOnTexture.second, dimensionOnTexture.first, dimensionOnTexture.second};
    SDL_Rect render_quad = {x+displacement.first, y+displacement.second, this->get_width(), this->get_height()};
    SDL_RenderCopy(renderer, texture, &ret, &render_quad);
}
