#ifndef TIMER
#define TIMER

#include "../include/SDL2basics.hpp"

namespace engine{

    class Timer{
    public:

        bool is_running;
        int initial_time;
        int time_interval;

        Timer()
            : is_running(false),
            initial_time(0),
            time_interval(0){}

            void init_timer();
            void stop_timer();
            void set_interval();
            int get_elapsed_time();
            int get_total_time();
    };

}

#endif