/**
 * @file timer.cpp
 * @brief Purpose: Contains timer's methods.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/ master/LICENSE.md
 */

#include "../include/timer.hpp"

using namespace engine;

/**
 * @brief Initialize the timer.
 *
 * This method initialize the timer.
 *
 * @return void.
 */

void Timer::init_timer() {
    is_running = true;
    initial_time = SDL_GetTicks();
    time_interval = initial_time;
}

/**
 * @brief Stop the timer.
 *
 * This method stop the timer if it has already been initialized.
 *
 * @return void.
 */

void Timer::stop_timer() {
    is_running = false;
    initial_time = 0;
    time_interval = initial_time;
}

/**
 * @brief Get total time of the game.
 *
 * This method get the total time of the game in milliseconds, but
 * just if is running.
 *
 * @return void.
 */

int Timer::get_total_time() {
    if (!is_running) {
        return 0;
    } 
    else {
        return SDL_GetTicks() - initial_time;
    }
}

/**
 * @brief Get elapsed time of the game.
 *
 * This method gets the elapsed time of the game, in milliseconds.
 *
 * @return void.
 */

int Timer::get_elapsed_time() {
    if (!is_running) {
        return 0;
    } 
    else {
        return SDL_GetTicks() - time_interval;
    }
}

/**
 * @brief Set interval of the game.
 *
 * This method set an interval, in milliseconds, on the timer if the timer
 * is defined with running.
 *
 * @return void.
 */

void Timer::set_interval() {
    if (!is_running) {
        printf("Cannot set interval while timer is stopped.");
    } 
    else {
        time_interval = get_total_time();
    }
}