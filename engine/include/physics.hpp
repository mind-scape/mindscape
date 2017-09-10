/**
* @file physics.hpp
* @brief Purpose: Contains the Physics class declaration.
*
* MIT License
* Copyright (c) 2017 MindScape
*
* https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
*/
#ifndef PHYSICS_H
#define PHYSICS_H

#include <iostream>
#include <string>
#include <vector>
#include "game_object.hpp"

namespace engine {
    /**
    * @brief A Physics class.
    *
    * A class responsible to ensure physics handling.
    *
    */
    class Physics {
    private:
        Physics(){};

        static Physics *instance;
        static std::vector<GameObject *> physicables;
        static float gravity;

        std::pair<float, float> calculate_speed(std::pair<float, float>);
        std::pair<float, float> calculate_position(std::pair<float, float>, std::pair<float, float>);
        void update_speed(GameObject *);
        void update_position(GameObject *);
        void act_on(GameObject *);
      
    public:
        static Physics *get_instance();
        ~Physics(){};

        void operator=(Physics const&) = delete;
        void add_physicable(GameObject *);
        float get_gravity();
        void act();
  };
}

#endif
