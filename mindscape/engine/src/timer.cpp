#include "../include/timer.hpp"

using namespace engine;

void Timer::init_timer(){
    is_running = true;
    initial_time = SDL_GetTicks();
    time_interval = initial_time;
}

void Timer::stop_timer(){
    is_running = false;
    initial_time = 0;
    time_interval = initial_time;
}

int Timer::get_total_time(){
    if(!is_running){
        return 0;
    } else {
        return SDL_GetTicks() - initial_time;
    }
}

int Timer::get_elapsed_time(){
    if(!is_running){
        return 0;
    } else {
        return SDL_GetTicks() - time_interval;
    }
}