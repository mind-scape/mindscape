/**
 * @file timer.hpp
 * @brief Purpose: Contains methods to timer's management.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#ifndef TIMER
#define TIMER

#include "../include/SDL2basics.hpp"

namespace engine {

    /**
     * @brief A Timer class.
     *
     * This class is responsible for build a timer for an specific occasion.
     */

    class Timer {
        public:

            bool is_running;
            int initial_time;
            int time_interval;

            Timer()
                : is_running(false),
                initial_time(0),
                time_interval(0){  
                }

            void init_timer();
            void stop_timer();
            void set_interval();
            int get_elapsed_time();
            int get_total_time();
    };
}

#endif
